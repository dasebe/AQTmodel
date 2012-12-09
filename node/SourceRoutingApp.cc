
#include <string.h>

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "../messages/SourceRoutingPacket_m.h"
#include "../messages/AdversarialInjectionMessage_m.h"



/**
 * Controlled by the adversary, receives injection commands and create corresponding packets.
 */
class SourceRoutingApp : public cSimpleModule
{
  private:
    // configuration
    int myAddress;
    cPar *packetLengthBytes;

    // state
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
}

SourceRoutingApp::~SourceRoutingApp()
{
}

void SourceRoutingApp::initialize()
{
    myAddress = par("address");
    packetLengthBytes = &par("packetLength");
    pkCounter = 0;

    WATCH(pkCounter);
    WATCH(myAddress);

    endToEndDelaySignal = registerSignal("endToEndDelay");
    hopCountSignal =  registerSignal("hopCount");
    sourceAddressSignal = registerSignal("sourceAddress");
}

void SourceRoutingApp::handleMessage(cMessage *msg)
{
    //if this is send by the Adversary and named sendPacket
    //const char * msgtype = msg->getClassName();

    if (msg->getKind() == 101)
    {
        //getting information about injection
        AdversarialInjectionMessage *pk = check_and_cast<AdversarialInjectionMessage *>(msg);

        // packet name
        char pkname[40];
        sprintf(pkname,"%s:    no %ld from node %d", pk->getName(), pkCounter++, myAddress);
        //EV << "node "  << myAddress << ": received injection command" << endl;

        //generate new Network Packet (SourceRoutingPacket)
        SourceRoutingPacket *npk = new SourceRoutingPacket(pkname);
        npk->setByteLength(packetLengthBytes->longValue());
        npk->setSrcAddr(myAddress);
        npk->setDestAddrArraySize(pk->getPathArraySize());
        npk->setSchedulingPriority(6); //higher means lower priority, adversarial messages get 1-2
        unsigned int i=0; //because array size is unsigned!
        while(i < (pk->getPathArraySize()))
        {
            npk->setDestAddr(i,pk->getPath(i)); //use build-in methods - more performance through call by reference... (not yet implemented)
            i++;
        }
        //send new packet to router
        send(npk,"out");

        //delete adversarial command
        delete(pk);
        //cancelAndDelete(msg);?


    }
    else if (msg->isPacket()) //no type/class check! -> assume only other poss is SourceRoutingPacket
    {
        // Handle incoming packet
        SourceRoutingPacket *pk = check_and_cast<SourceRoutingPacket *>(msg);
        EV << "ARRIVAL:    pf " << pk->getName() << " at " << pk->getDestAddr(0) << " hops " << pk->getHopCount() << endl;
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
    //else unknown message
}

