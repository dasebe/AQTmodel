#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "AdversarialInjectionMessage_m.h"
#include "AdvancedAdversary.h"

/**
 * Generates and schedules injections for the nodes in the network.
 */
class CE7Advanced : public AdvancedAdversary
{
  protected:
    void injectInitialPackets();
    void injectPhasePackets();

};

Define_Module(CE7Advanced);



void CE7Advanced::injectInitialPackets()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    noInjs = 3+3+3+3+3; //3initial sets, 3x3injections + 3 direct injects
    injections = (Inj*) malloc(noInjs*sizeof(Inj));
    int initialSetSize=10; //in time steps (not simulationTime!!)
    Inj * tmp;
    int tmpi=0;

//learn queue length
    //before the queue length later on can be queried -> need to create the listener objects

    //init listener (even at first time want to check whether subscribed)
    listener = new QueueListener();

    cModule *targetModule = getParentModule()->getSubmodule("a1")->getSubmodule("routing");
    cMessage *queueLenMsg = new cMessage("queue length a1-a2?");
    (*queueLenMsg).addPar("queueLenQ");
    (*queueLenMsg).par("queueLenQ").setLongValue(12);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");






//round 0
    // (initial packets A)
    tmp = &injections[tmpi];
    (*tmp).interInjectionTime = 0;
    (*tmp).interInjectionTime = 0;
    (*tmp).packetCount=initialSetSize;
    (*tmp).message =  new AdversarialInjectionMessage("initial set A0");
    (*tmp).atNode = "a1";
    (*tmp).message->setPathArraySize(1);
    (*tmp).message->setPath(0,12);
    (*tmp).message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: A0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(simTime() + 0*(timeSlots->doubleValue()), selfNote);


//round 1
    timeSync = simTime(); //offset for first round = 0


//round 2
    timeSync += initialSetSize*(timeSlots->doubleValue());

    // (initial packets B)
    tmp = &injections[tmpi];
    (*tmp).interInjectionTime = 0;
    (*tmp).packetCount= initialSetSize;
    (*tmp).message =  new AdversarialInjectionMessage("initial set B0");
    (*tmp).atNode = "b1";
    (*tmp).message->setPathArraySize(3);
    (*tmp).message->setPath(0,92);
    (*tmp).message->setPath(1,91);
    (*tmp).message->setPath(2,22);
    (*tmp).message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: B0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


//round 3
    timeSync += initialSetSize*(timeSlots->doubleValue());

    // (initial packets C)
    tmp = &injections[tmpi];
    (*tmp).interInjectionTime = 0;
    (*tmp).packetCount=initialSetSize;
    (*tmp).message =  new AdversarialInjectionMessage("initial set C0");
    (*tmp).atNode = "c1";
    (*tmp).message->setPathArraySize(5);
    (*tmp).message->setPath(0,93);
    (*tmp).message->setPath(1,92);
    (*tmp).message->setPath(2,95);
    (*tmp).message->setPath(3,94);
    (*tmp).message->setPath(4,32);
    (*tmp).message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: C0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


}







    void CE7Advanced::injectPhasePackets()
    {
        Inj * tmp;
        int tmpi=0;
        //we assume we are not subscribed to the right queue! - no further consistency check!
        overallRoundTime=listener->queuelength + 1; //because one transmitted right away
        ev << "got queue length: "<< overallRoundTime << endl;

//round 1
        timeSync = simTime(); //offset for first round = 0


        // (set A1)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set A1");
        (*tmp).atNode = "a1";
        (*tmp).message->setPathArraySize(6);
        (*tmp).message->setPath(0,14);
        (*tmp).message->setPath(1,13);
        (*tmp).message->setPath(2,93);
        (*tmp).message->setPath(3,92);
        (*tmp).message->setPath(4,91);
        (*tmp).message->setPath(5,12);//first hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 2
        timeSync += overallRoundTime*(timeSlots->doubleValue());

        // (set A2)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set A2");
        (*tmp).atNode = "a1";
        (*tmp).message->setPathArraySize(5);
        (*tmp).message->setPath(0,14);
        (*tmp).message->setPath(1,13);
        (*tmp).message->setPath(2,95);
        (*tmp).message->setPath(3,94);
        (*tmp).message->setPath(4,12);//first hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B1)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set B1");
        (*tmp).atNode = "b1";
        (*tmp).message->setPathArraySize(9);
        (*tmp).message->setPath(0,97);//last hop
        (*tmp).message->setPath(1,96);
        (*tmp).message->setPath(2,25);
        (*tmp).message->setPath(3,24);
        (*tmp).message->setPath(4,23);
        (*tmp).message->setPath(5,93);
        (*tmp).message->setPath(6,92);
        (*tmp).message->setPath(7,91);
        (*tmp).message->setPath(8,22);//first hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 3
        timeSync += overallRoundTime*(timeSlots->doubleValue());


        // (set A3)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set A3");
        (*tmp).atNode = "a1";
        (*tmp).message->setPathArraySize(3);
        (*tmp).message->setPath(0,14); //last hop
        (*tmp).message->setPath(1,13);
        (*tmp).message->setPath(2,12);//first hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B2)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set B2");
        (*tmp).atNode = "b1";
        (*tmp).message->setPathArraySize(8);
        (*tmp).message->setPath(0,97);
        (*tmp).message->setPath(1,96);
        (*tmp).message->setPath(2,25);
        (*tmp).message->setPath(3,24);
        (*tmp).message->setPath(4,23);
        (*tmp).message->setPath(5,95);
        (*tmp).message->setPath(6,94);
        (*tmp).message->setPath(7,22);
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C1)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set C1");
        (*tmp).atNode = "c1";
        (*tmp).message->setPathArraySize(10);
        (*tmp).message->setPath(0,98);
        (*tmp).message->setPath(1,97);
        (*tmp).message->setPath(2,99);
        (*tmp).message->setPath(3,35);
        (*tmp).message->setPath(4,34);
        (*tmp).message->setPath(5,33);
        (*tmp).message->setPath(6,93);
        (*tmp).message->setPath(7,92);
        (*tmp).message->setPath(8,91);
        (*tmp).message->setPath(9,32);
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 4
        timeSync += overallRoundTime*(timeSlots->doubleValue());

        // (set A4) direct inject
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set A4");
        (*tmp).atNode = "a3";
        (*tmp).message->setPathArraySize(1);
        (*tmp).message->setPath(0,14); //last hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B3)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set B3");
        (*tmp).atNode = "b1";
        (*tmp).message->setPathArraySize(6);
        (*tmp).message->setPath(0,97);
        (*tmp).message->setPath(1,96);
        (*tmp).message->setPath(2,25);
        (*tmp).message->setPath(3,24);
        (*tmp).message->setPath(4,23);
        (*tmp).message->setPath(5,22);
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C2)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set C2");
        (*tmp).atNode = "c1";
        (*tmp).message->setPathArraySize(9);
        (*tmp).message->setPath(0,98);
        (*tmp).message->setPath(1,97);
        (*tmp).message->setPath(2,99);
        (*tmp).message->setPath(3,35);
        (*tmp).message->setPath(4,34);
        (*tmp).message->setPath(5,33);
        (*tmp).message->setPath(6,95);
        (*tmp).message->setPath(7,94);
        (*tmp).message->setPath(8,32);
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 5
        timeSync += overallRoundTime*(timeSlots->doubleValue());

        // (set B4) direct inject
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set B4");
        (*tmp).atNode = "b3";
        (*tmp).message->setPathArraySize(1);
        (*tmp).message->setPath(0,24); //last hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C3)
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set C3");
        (*tmp).atNode = "c1";
        (*tmp).message->setPathArraySize(7);
        (*tmp).message->setPath(0,98);
        (*tmp).message->setPath(1,97);
        (*tmp).message->setPath(2,99);
        (*tmp).message->setPath(3,35);
        (*tmp).message->setPath(4,34);
        (*tmp).message->setPath(5,33);
        (*tmp).message->setPath(6,32);
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

//round 6
        timeSync += overallRoundTime*(timeSlots->doubleValue());

        // (set A4) direct inject
        tmp = &injections[tmpi];
        (*tmp).interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        (*tmp).packetCount=floor(bufferSize*injectionRate);
        (*tmp).message =  new AdversarialInjectionMessage("set C4");
        (*tmp).atNode = "c3";
        (*tmp).message->setPathArraySize(1);
        (*tmp).message->setPath(0,34); //last hop
        (*tmp).message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);
    }
