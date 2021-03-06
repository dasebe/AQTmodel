#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "AdversarialInjectionMessage_m.h"


/**
 * message kinds:
 * 0-99:  adversarial rounds (injection round)
 * 101:   adversarial command
 */

/**
 * Generates traffic for the network.
 */
class CE3half : public cSimpleModule
{
  private:
    // configuration
    cPar *timeSlots;
    long bufferSize;
    double injectionRate;
    SimTime timeSync;
    int noInjs;

    struct Inj
    {
        long packetCount;   // [start,stop] time range for injection
        const char* atNode;         // where to initially deploy the packets upon injection
        double interInjectionTime;  // 1/injectionRate - will directly go into the offset for scheduleAt events
        AdversarialInjectionMessage *message; //adversarial injection command to be send to nodes
        int packetNHops;
        int *packetPath;    // path injected together with the packets (possibly of unkown length)
    };

    // state
    Inj *injections;
    cMessage *selfNote; //self-messaging
    long injectionCount;

    // signals for statistics (e.g.)
    simsignal_t injectedPackets;

  public:
    CE3half();
    virtual ~CE3half();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(CE3half);


CE3half::CE3half()
{
    selfNote = NULL;
}

CE3half::~CE3half()
{
    for (int i=0; i < noInjs;i++)
    {
        cancelAndDelete(injections[i].message);
    }
    //cancelAndDelete(selfNote);
    //delete(injections);
}

void CE3half::initialize()
{
    timeSlots = &par("timeSlotLength");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    noInjs = 5;
    injections = (Inj*) malloc(noInjs*sizeof(Inj));

    //class 0 (initial packets)
    injections[0].interInjectionTime = 0;
    injections[0].packetCount=bufferSize;
    injections[0].message =  new AdversarialInjectionMessage("initial set");
    injections[0].atNode = "v0";
    injections[0].message->setPathArraySize(1);
    injections[0].message->setPath(0,111);//first hop
    injections[0].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 0");
    selfNote->setKind(0); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(simTime() + 0*(timeSlots->doubleValue()), selfNote);

    //class 1 (round 1)
    int overallRoundTime=bufferSize; //in time steps (not simulationTime!!)
    injections[1].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[1].packetCount= floor(overallRoundTime*injectionRate);
    injections[1].message =  new AdversarialInjectionMessage("set 1");
    injections[1].atNode = "v0";
    injections[1].message->setPathArraySize(4);
    injections[1].message->setPath(0,211); //last hop
    injections[1].message->setPath(1,131);
    injections[1].message->setPath(2,121);
    injections[1].message->setPath(3,111);//first hop
    injections[1].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 1");
    selfNote->setKind(1); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(simTime() + 0*(timeSlots->doubleValue()), selfNote);

    //class 2 (round 2) confinement packets
    injections[2].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[2].packetCount=floor(bufferSize/2*injectionRate);
    injections[2].message =  new AdversarialInjectionMessage("confinement 1");
    injections[2].atNode = "w0";
    injections[2].message->setPathArraySize(1);
    injections[2].message->setPath(0,121);
    injections[2].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 2");
    selfNote->setKind(2); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    timeSync = simTime() + overallRoundTime*(timeSlots->doubleValue());
    scheduleAt(timeSync, selfNote);

    //class 3 (round 2)
    injections[3].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[3].packetCount=floor(bufferSize*injectionRate);
    injections[3].message =  new AdversarialInjectionMessage("set 2");
    injections[3].atNode = "v0";
    injections[3].message->setPathArraySize(4);
    injections[3].message->setPath(0,211); //last hop
    injections[3].message->setPath(1,131);
    injections[3].message->setPath(2,122);
    injections[3].message->setPath(3,111);//first hop
    injections[3].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 3");
    selfNote->setKind(3); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 4 (round 3)
    injections[4].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[4].packetCount=floor(bufferSize*injectionRate);
    injections[4].message =  new AdversarialInjectionMessage("set 3");
    injections[4].atNode = "v1";
    injections[4].message->setPathArraySize(1);
    injections[4].message->setPath(0,211);
    injections[4].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 4");
    selfNote->setKind(4); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    timeSync += overallRoundTime*(timeSlots->doubleValue());
    scheduleAt(timeSync, selfNote);


    injectedPackets = registerSignal("injectedPackets");
}



void CE3half::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage()) //only for events schedule by myself
    {

        //const char * name = msg->getName();
        int cl = msg->getKind();

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule(injections[cl].atNode)->getSubmodule("app");

        //we already have a message defined in our Inj struct

        if (injections[cl].packetCount-- > 0) //only send a message if remaining
        {
            //send duplicate of message, as we won't be the owner after it has been passed to targetModule
            emit(injectedPackets, ++injectionCount);

            sendDirect(injections[cl].message->dup(), targetModule, "adversaryControl");

            if (ev.isGUI()) getParentModule()->bubble("injecting round 0");

            EV << "INJECT:     at " << injections[cl].atNode << "  set " << cl << "  remain " << injections[cl].packetCount << endl;

            char pkname[40];
            sprintf(pkname,"next  in %d remain %ld", cl, injections[cl].packetCount);
            selfNote = new cMessage(pkname);
            selfNote->setKind(cl); //this means that the first entry of the injection struct shall be started by this message
            selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
            scheduleAt(simTime() + injections[cl].interInjectionTime, selfNote);
        }
        cancelAndDelete(msg);
    }
}

