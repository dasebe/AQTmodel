//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <string.h>

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "SourceRoutingPacket_m.h"
#include "AdversarialInjectionMessage_m.h"



/**
 * Generates traffic for the network.
 */
class SourceRoutingApp : public cSimpleModule
{
  private:
    // configuration
    int myAddress;
    std::vector<int> destAddresses;
    cPar *sendIATime;
    cPar *packetLengthBytes;

    // state
    cMessage *generatePacket;
    long pkCounter;

    // signals
    simsignal_t endToEndDelaySignal;
    simsignal_t hopCountSignal;
    simsignal_t sourceAddressSignal;

  public:
    SourceRoutingApp();
    virtual ~SourceRoutingApp();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(SourceRoutingApp);


SourceRoutingApp::SourceRoutingApp()
{
    generatePacket = NULL;
}

SourceRoutingApp::~SourceRoutingApp()
{
    cancelAndDelete(generatePacket);
}

void SourceRoutingApp::initialize()
{
    myAddress = par("address");
    packetLengthBytes = &par("packetLength");
    sendIATime = &par("sendIaTime");  // volatile parameter
    pkCounter = 0;

    WATCH(pkCounter);
    WATCH(myAddress);

    //parse destAddresses from String
    const char *destAddressesPar = par("destAddresses");
    cStringTokenizer tokenizer(destAddressesPar);
    const char *token;
    while ((token = tokenizer.nextToken())!=NULL)
        destAddresses.push_back(atoi(token));


    if (destAddresses.size() == 0)
        throw cRuntimeError("At least one address must be specified in the destAddresses parameter!");

//    generatePacket = new cMessage("nextPacket");
//    scheduleAt(sendIATime->doubleValue(), generatePacket);

    endToEndDelaySignal = registerSignal("endToEndDelay");
    hopCountSignal =  registerSignal("hopCount");
    sourceAddressSignal = registerSignal("sourceAddress");
}

void SourceRoutingApp::handleMessage(cMessage *msg)
{
    //const char *  x = msg->getArrivalGate()->getFullName();

    //if this is send by the Adversary and named sendPacket
    if (strcmp (msg->getFullName(),"injection")==0)
    {
        //getting information about injection
        AdversarialInjectionMessage *pk = check_and_cast<AdversarialInjectionMessage *>(msg);


        // Sending packet
        char pkname[40];
        //what about pkname??
        sprintf(pkname,"node %d, new pkt, send packets: %ld", myAddress, pkCounter++);
        EV << "node "  << myAddress << ": received injection command" << endl;

        //generate new Network Packet (SourceRoutingPacket)
        SourceRoutingPacket *npk = new SourceRoutingPacket(pkname);
        npk->setByteLength(packetLengthBytes->longValue());
        npk->setSrcAddr(myAddress);
        npk->setDestAddrArraySize(pk->getPathArraySize());
        unsigned int i=0; //because array size is unsigned!
        while(i < (pk->getPathArraySize()))
        {
            npk->setDestAddr(i,pk->getPath(i));
            i++;
        }
        //send new packet to router
        send(npk,"out");

        //delete adversarial command
        delete(pk);


    }
    else
    {
        // Handle incoming packet
        SourceRoutingPacket *pk = check_and_cast<SourceRoutingPacket *>(msg);
        EV << "received packet " << pk->getName() << " after " << pk->getHopCount() << "hops" << endl;
        emit(endToEndDelaySignal, simTime() - pk->getCreationTime());
        emit(hopCountSignal, pk->getHopCount());
        emit(sourceAddressSignal, pk->getSrcAddr());
        delete pk;

        if (ev.isGUI())
        {
            getParentModule()->getDisplayString().setTagArg("i",1,"green");
            getParentModule()->bubble("Arrived!");
        }
    }
}

