#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifndef OMNETPP_H
#define OMNETPP_H
 #include <omnetpp.h>
#endif

#include <vector>
#include "AdversarialInjectionMessage_m.h"


/**
 * message kinds:
 * 0-99:  adversarial rounds (injection round)
 * 101:   adversarial command
 */

/**
 * Generates traffic for the network.
 */
class CE7half : public cSimpleModule
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
    CE7half();
    virtual ~CE7half();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(CE7half);


CE7half::CE7half()
{
    selfNote = NULL;
}

CE7half::~CE7half()
{
    for (int i=0; i < noInjs;i++)
    {
        cancelAndDelete(injections[i].message);
    }
    //cancelAndDelete(selfNote);
    //delete(injections);
}

void CE7half::initialize()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    noInjs = 3+1+3+3+3; //3initial sets, 1confinement, 3x3injections
    injections = (Inj*) malloc(noInjs*sizeof(Inj));
    int overallRoundTime=bufferSize; //in time steps (not simulationTime!!)


//round 0
    //class 0 (initial packets A)  //////modified version
    injections[0].interInjectionTime = 0;
    injections[0].packetCount=bufferSize;
    injections[0].message =  new AdversarialInjectionMessage("initial set A0");
    injections[0].atNode = "a0";
    injections[0].message->setPathArraySize(4);
    injections[0].message->setPath(0,12);
    injections[0].message->setPath(1,11);
    injections[0].message->setPath(2,102);
    injections[0].message->setPath(3,101);
    injections[0].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 0");
    selfNote->setKind(0); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(simTime() + 0*(timeSlots->doubleValue()), selfNote);


//round 1
    timeSync = simTime(); //offset for first round = 0


    //class 2 (set A1)
    injections[2].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[2].packetCount=floor(bufferSize*injectionRate);
    injections[2].message =  new AdversarialInjectionMessage("set A1");
    injections[2].atNode = "a0";
    injections[2].message->setPathArraySize(8);
    injections[2].message->setPath(0,14); //last hop
    injections[2].message->setPath(1,13);
    injections[2].message->setPath(2,93);
    injections[2].message->setPath(3,91);
    injections[2].message->setPath(4,12);
    injections[2].message->setPath(5,11);
    injections[2].message->setPath(6,103);
    injections[2].message->setPath(7,101);//first hop
    injections[2].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 2");
    selfNote->setKind(2); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 3 (confinement for A0)
    injections[3].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[3].packetCount=floor(bufferSize*injectionRate);
    injections[3].message =  new AdversarialInjectionMessage("confinement 1");
    injections[3].atNode = "a01";
    injections[3].message->setPathArraySize(1);
    injections[3].message->setPath(0,102); //last hop
    injections[3].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 3");
    selfNote->setKind(3); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


//round 2
    timeSync += overallRoundTime*(timeSlots->doubleValue());

    //class 1 (initial packets B)
    injections[1].interInjectionTime = 0;
    injections[1].packetCount= overallRoundTime;
    injections[1].message =  new AdversarialInjectionMessage("initial set B0");
    injections[1].atNode = "b0";
    injections[1].message->setPathArraySize(3);
    injections[1].message->setPath(0,92);
    injections[1].message->setPath(1,91);
    injections[1].message->setPath(2,22);
    injections[1].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 1");
    selfNote->setKind(1); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 5 (set A2)
    injections[5].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[5].packetCount=floor(bufferSize*injectionRate);
    injections[5].message =  new AdversarialInjectionMessage("set A2");
    injections[5].atNode = "a0";
    injections[5].message->setPathArraySize(8);
    injections[5].message->setPath(0,14); //last hop
    injections[5].message->setPath(1,13);
    injections[5].message->setPath(2,95);
    injections[5].message->setPath(3,94);
    injections[5].message->setPath(4,12);
    injections[5].message->setPath(5,11);
    injections[5].message->setPath(6,103);
    injections[5].message->setPath(7,101);//first hop
    injections[5].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 5");
    selfNote->setKind(5); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 6 (set B1)
    injections[6].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[6].packetCount=floor(bufferSize*injectionRate);
    injections[6].message =  new AdversarialInjectionMessage("set B1");
    injections[6].atNode = "b0";
    injections[6].message->setPathArraySize(6);
    injections[6].message->setPath(0,24); //last hop
    injections[6].message->setPath(1,23);
    injections[6].message->setPath(2,93);
    injections[6].message->setPath(3,91);
    injections[6].message->setPath(4,22);
    injections[6].message->setPath(5,21);
    injections[6].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 6");
    selfNote->setKind(6); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

//round 3
    timeSync += overallRoundTime*(timeSlots->doubleValue());

    //class 4 (initial packets C)
    injections[4].interInjectionTime = 0;
    injections[4].packetCount=overallRoundTime;
    injections[4].message =  new AdversarialInjectionMessage("initial set C0");
    injections[4].atNode = "c0";
    injections[4].message->setPathArraySize(3);
    injections[4].message->setPath(0,95);
    injections[4].message->setPath(1,94);
    injections[4].message->setPath(2,32);
    injections[4].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 4");
    selfNote->setKind(4); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


    //class 7 (set A3)
    injections[7].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[7].packetCount=floor(bufferSize*injectionRate);
    injections[7].message =  new AdversarialInjectionMessage("set A3");
    injections[7].atNode = "a0";
    injections[7].message->setPathArraySize(6);
    injections[7].message->setPath(0,14); //last hop
    injections[7].message->setPath(1,13);
    injections[7].message->setPath(2,12);
    injections[7].message->setPath(3,11);
    injections[7].message->setPath(4,103);
    injections[7].message->setPath(5,101);//first hop
    injections[7].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 7");
    selfNote->setKind(7); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 8 (set B2)
    injections[8].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[8].packetCount=floor(bufferSize*injectionRate);
    injections[8].message =  new AdversarialInjectionMessage("set B2");
    injections[8].atNode = "b0";
    injections[8].message->setPathArraySize(6);
    injections[8].message->setPath(0,24); //last hop
    injections[8].message->setPath(1,23);
    injections[8].message->setPath(2,95);
    injections[8].message->setPath(3,94);
    injections[8].message->setPath(4,22);
    injections[8].message->setPath(5,21);
    injections[8].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 8");
    selfNote->setKind(8); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 9 (set C1)
    injections[9].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[9].packetCount=floor(bufferSize*injectionRate);
    injections[9].message =  new AdversarialInjectionMessage("set C1");
    injections[9].atNode = "c0";
    injections[9].message->setPathArraySize(6);
    injections[9].message->setPath(0,34); //last hop
    injections[9].message->setPath(1,33);
    injections[9].message->setPath(2,93);
    injections[9].message->setPath(3,91);
    injections[9].message->setPath(4,32);
    injections[9].message->setPath(5,31);
    injections[9].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 9");
    selfNote->setKind(9); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


//round 4
    timeSync += overallRoundTime*(timeSlots->doubleValue());

    //class 10 (set B3)
    injections[10].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[10].packetCount=floor(bufferSize*injectionRate);
    injections[10].message =  new AdversarialInjectionMessage("set B3");
    injections[10].atNode = "b0";
    injections[10].message->setPathArraySize(4);
    injections[10].message->setPath(0,24); //last hop
    injections[10].message->setPath(1,23);
    injections[10].message->setPath(2,22);
    injections[10].message->setPath(3,21);
    injections[10].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 10");
    selfNote->setKind(10); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    //class 11 (set C2)
    injections[11].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[11].packetCount=floor(bufferSize*injectionRate);
    injections[11].message =  new AdversarialInjectionMessage("set C2");
    injections[11].atNode = "c0";
    injections[11].message->setPathArraySize(6);
    injections[11].message->setPath(0,34); //last hop
    injections[11].message->setPath(1,33);
    injections[11].message->setPath(2,95);
    injections[11].message->setPath(3,94);
    injections[11].message->setPath(4,32);
    injections[11].message->setPath(5,31);
    injections[11].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 11");
    selfNote->setKind(11); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


    //round 5
    timeSync += overallRoundTime*(timeSlots->doubleValue());

    //class 12 (set C3)
    injections[12].interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    injections[12].packetCount=floor(bufferSize*injectionRate);
    injections[12].message =  new AdversarialInjectionMessage("set C3");
    injections[12].atNode = "c0";
    injections[12].message->setPathArraySize(4);
    injections[12].message->setPath(0,34); //last hop
    injections[12].message->setPath(1,33);
    injections[12].message->setPath(2,32);
    injections[12].message->setPath(3,31);
    injections[12].message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("start injection 12");
    selfNote->setKind(12); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 2 (default value is 0)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


    injectedPackets = registerSignal("injectedPackets");
}



void CE7half::handleMessage(cMessage *msg)
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

