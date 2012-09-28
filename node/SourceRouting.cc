//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <map>
#include <omnetpp.h>
#include "SourceRoutingPacket_m.h"
//#include "QueueListener.cc"


/**
 * Demonstrates static routing, utilizing the cTopology class.
 */
class SourceRouting : public cSimpleModule
{
  private:
    int myAddress;
    long queueLen;

    typedef std::map<int,int> RoutingTable; // destaddr -> gateindex
    RoutingTable rtable;

    simsignal_t dropSignal;
    simsignal_t outputIfSignal;

    /*listener class as
    * cListener is only "A do-nothing implementation of cIListener, suitable as a base class for other listeners."
    * and we need to "redefine one or more of the overloaded receiveSignal() methods" */

    class QueueListener : public cListener {
        public:
            long queuelength;
            QueueListener(){}
            void receiveSignal (cComponent *source, simsignal_t signalID, long l){
                ev << "Signal received" << l << endl;
                queuelength=l;
                source->getFullPath();
            }
    };

    QueueListener *listener;



  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void receiveSignal(cComponent *src, simsignal_t id, long l);
};

Define_Module(SourceRouting);


void SourceRouting::initialize()
{
    myAddress = getParentModule()->par("address");

    dropSignal = registerSignal("drop");
    outputIfSignal = registerSignal("outputIf");


    //
    // Brute force approach -- every node does topology discovery on its own,
    // and finds routes to all other nodes independently, at the beginning
    // of the simulation. This could be improved: (1) central routing database,
    // (2) on-demand route calculation
    //
    cTopology *topo = new cTopology("topo");

    std::vector<std::string> nedTypes;
    nedTypes.push_back(getParentModule()->getNedTypeName());
    topo->extractByNedTypeName(nedTypes);
    EV << "cTopology found " << topo->getNumNodes() << " nodes\n";

    cTopology::Node *thisNode = topo->getNodeFor(getParentModule());

    //probably needs fix
    // find and store next hops by unweighted SSP
    for (int i=0; i<topo->getNumNodes(); i++)
    {
        if (topo->getNode(i)==thisNode) continue; // skip ourselves
        topo->calculateUnweightedSingleShortestPathsTo(topo->getNode(i));

        if (thisNode->getNumPaths()==0) continue; // not connected

        cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();
        int gateIndex = parentModuleGate->getIndex();
        int address = topo->getNode(i)->getModule()->par("address");
        rtable[address] = gateIndex;
        EV << "RTABLE:    towards address " << address << " gateIndex is " << gateIndex << endl;
    }
    delete topo;

    //init listener (even at first time want to check whether subscribed)
    listener = new QueueListener();

}



void SourceRouting::receiveSignal(cComponent *src, simsignal_t id, long l){
    ev << "Signal received" << "the queue length of " << (*src).getFullPath() <<" is " << l << endl;
    queueLen = l;
}



void SourceRouting::handleMessage(cMessage *msg)
{
    /*two principal possibilities for messages:
     *  1. QueueLength Packets which wants to obtain the current queue length
     *  2. SourceRoutingPacket need be forwarded,absorbed,...
     */



    //TODO it's not correct implementing this here, should be at node level!
    if (msg->hasPar("queueLenQ"))
    {

        //we need send back a queue length response for the fitting gate!
        long int outHop = msg->par("queueLenQ").longValue();
        //lookup in RoutingTable
        RoutingTable::iterator it = rtable.find(outHop);
        if (it==rtable.end())
        {
            //EV << "FAIL   : retrieving queue length"
            return;
        }

        int outGateIndex = (*it).second;
        int qlen=0;

        //check whether already subscribed
        if (!isSubscribed("qlen", listener))
        {
            getParentModule()->getSubmodule("queue",outGateIndex)->subscribe("qlen", listener);
        }

        //we assume we are not subscribed to the right queue! - no further consistency check!
        qlen=listener->queuelength;

        cMessage *answer = new cMessage("answer queue length");
        answer->addPar("qlen");
        answer->addPar("qlen").setLongValue(qlen);
        cModule *adversary = msg->getSenderModule();
        sendDirect(answer, adversary, "adversaryControl$i");
        cancelAndDelete(msg);
    }





    else
    {
        //assume it's an SourceRoutingPacket (might as well omit the try block)
        SourceRoutingPacket *pk = check_and_cast<SourceRoutingPacket *>(msg);
        int remDestCount = pk->getDestAddrArraySize();
        int curDestAddr = pk->getDestAddr(remDestCount-1); //currentAddress is last one in array

        //case final destination
        if (curDestAddr == myAddress && remDestCount == 1)
        {
            //EV << "local delivery of packet " << pk->getName() << endl;
            send(pk, "localOut");
            emit(outputIfSignal, -1); // -1: local
            return;
        }

        //case intermediate (source-route) destination
        if (curDestAddr == myAddress && remDestCount > 1)
        {
            EV << "IHOP:      at " << myAddress << "packet" << pk->getName() << endl;
            //delete curDestAddr, by decreasing array size by one
            pk->setDestAddrArraySize(--remDestCount);
            //set "old next" destination as current one
            curDestAddr = pk->getDestAddr(remDestCount-1);
            //we still have to forward it, so don't return yet!
        }

        //case intermediate hop, simple forward
        RoutingTable::iterator it = rtable.find(curDestAddr);
        if (it==rtable.end())
        {
            EV << "address " << curDestAddr << " unreachable from address " << myAddress << ", discarding packet " << pk->getName() << endl;
            emit(dropSignal, (long)pk->getByteLength());
            delete pk;
            return;
        }

        int outGateIndex = (*it).second;
        //EV << "forwarding packet " << pk->getName() << " on gate index " << outGateIndex << endl;
        pk->setHopCount(pk->getHopCount()+1);
        emit(outputIfSignal, outGateIndex);

        send(pk, "out", outGateIndex);
    }

}
