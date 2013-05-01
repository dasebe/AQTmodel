#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifndef OMNETPP_H
#define OMNETPP_H
 #include <omnetpp.h>
#endif

#include "../messages/AdversarialInjectionMessage_m.h"
#include "../messages/AdvSchedMess.h"
#include "AdvancedAdversary.h"

/**
 * Generates and schedules injections for the nodes in the network.
 */
class CE75 : public AdvancedAdversary
{
  protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(CE75);



void CE75::injectInitialPackets()
{
    timeSlots = &par("timeSlotLength");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    intervalStart = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    int initialSetSize=par("initialSetSize"); //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;
    phaseCounter=100; //currently overall time fixed to simTime<=100s

//learn queue length
    //before the queue length later on can be queried -> need to create the listener objects
    cModule *targetModule = getParentModule()->getSubmodule("n11")->getSubmodule("routing");
    QueueLengthRequest *queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("n11");
    queueLenMsg->setOutAddress(112);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

    targetModule = getParentModule()->getSubmodule("m11")->getSubmodule("routing");
    queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("m11");
    queueLenMsg->setOutAddress(212);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

//  set where to start (left site of gadget)
    curPhaseName='n';
    curPhaseCounter=100;
    nextPhaseName='m';
    nextPhaseCounter=200;

//round 0
    // (initial packets A)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime=0;
    tmp->packetCount=initialSetSize;
    tmp->message=new AdversarialInjectionMessage("initial set A0");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x11");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(1);
    tmp->message->setPath(0,curPhaseCounter+12);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this now as selfmessage
    scheduleAt(intervalStart,tmp);


//round 1
    intervalStart = simTime(); //offset for first round = 0


//round 2
    intervalStart += initialSetSize*(timeSlots->doubleValue());

    // (initial packets B)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = 0;
    tmp->packetCount= initialSetSize;
    tmp->message =  new AdversarialInjectionMessage("initial set B0");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x21");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(3);
    tmp->message->setPath(0,curPhaseCounter+92);
    tmp->message->setPath(1,curPhaseCounter+91);
    tmp->message->setPath(2,curPhaseCounter+22);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this now as selfmessage
    scheduleAt(intervalStart,tmp);


//round 3
    intervalStart += initialSetSize*(timeSlots->doubleValue());

    // (initial packets C)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = 0;
    tmp->packetCount=initialSetSize;
    tmp->message =  new AdversarialInjectionMessage("initial set C0");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x31");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(5);
    tmp->message->setPath(0,curPhaseCounter+93);
    tmp->message->setPath(1,curPhaseCounter+92);
    tmp->message->setPath(2,curPhaseCounter+95);
    tmp->message->setPath(3,curPhaseCounter+94);
    tmp->message->setPath(4,curPhaseCounter+32);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this now as selfmessage
    scheduleAt(intervalStart,tmp);

//round 4
        intervalStart += initialSetSize*(timeSlots->doubleValue());

        // (initial packets D)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = 0;
        tmp->packetCount=initialSetSize;
        tmp->message =  new AdversarialInjectionMessage("initial set D0");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x41");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+42);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(1);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

//round 5
        intervalStart += initialSetSize*(timeSlots->doubleValue());

        // (initial packets E)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = 0;
        tmp->packetCount=initialSetSize;
        tmp->message =  new AdversarialInjectionMessage("initial set E0");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x51");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+52);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(1);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);
}







    void CE75::injectPhasePackets()
    {
        AdvSchedMess * tmp;
        //we assume we are indeed subscribed to the right queue! - no further consistency check!
        long roundTime=qlarray[curPhaseCounter/100-1]->queuelength + 1; //because one transmitted right away
        emit(measuredSetSizeSignal, roundTime);
        ev << "QL: "<< roundTime << endl;

//round 1
        intervalStart = simTime(); //offset for first round = 0


        // (set A1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(6);
        tmp->message->setPath(0,nextPhaseCounter+12);
        tmp->message->setPath(1,nextPhaseCounter+11);
        tmp->message->setPath(2,curPhaseCounter+93);
        tmp->message->setPath(3,curPhaseCounter+92);
        tmp->message->setPath(4,curPhaseCounter+91);
        tmp->message->setPath(5,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);



//round 2
        intervalStart += roundTime*(timeSlots->doubleValue());

        // (set A2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(5);
        tmp->message->setPath(0,nextPhaseCounter+12);
        tmp->message->setPath(1,nextPhaseCounter+11);
        tmp->message->setPath(2,curPhaseCounter+95);
        tmp->message->setPath(3,curPhaseCounter+94);
        tmp->message->setPath(4,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set B1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(8);
        tmp->message->setPath(0,nextPhaseCounter+92);//last hop
        tmp->message->setPath(1,nextPhaseCounter+91);
        tmp->message->setPath(2,nextPhaseCounter+22);
        tmp->message->setPath(3,nextPhaseCounter+21);
        tmp->message->setPath(4,curPhaseCounter+93);
        tmp->message->setPath(5,curPhaseCounter+92);
        tmp->message->setPath(6,curPhaseCounter+91);
        tmp->message->setPath(7,curPhaseCounter+22);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);


//round 3
        intervalStart += roundTime*(timeSlots->doubleValue());


        // (set A3)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,nextPhaseCounter+12); //last hop
        tmp->message->setPath(1,nextPhaseCounter+11);
        tmp->message->setPath(2,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set B2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,nextPhaseCounter+92);
        tmp->message->setPath(1,nextPhaseCounter+91);
        tmp->message->setPath(2,nextPhaseCounter+22);
        tmp->message->setPath(3,nextPhaseCounter+21);
        tmp->message->setPath(4,curPhaseCounter+95);
        tmp->message->setPath(5,curPhaseCounter+94);
        tmp->message->setPath(6,curPhaseCounter+22);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set C1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x31");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(10);
        tmp->message->setPath(0,nextPhaseCounter+93);
        tmp->message->setPath(1,nextPhaseCounter+92);
        tmp->message->setPath(2,nextPhaseCounter+95);
        tmp->message->setPath(3,nextPhaseCounter+94);
        tmp->message->setPath(4,nextPhaseCounter+32);
        tmp->message->setPath(5,nextPhaseCounter+31);
        tmp->message->setPath(6,curPhaseCounter+93);
        tmp->message->setPath(7,curPhaseCounter+92);
        tmp->message->setPath(8,curPhaseCounter+91);
        tmp->message->setPath(9,curPhaseCounter+32);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);


//round 4
        intervalStart += roundTime*(timeSlots->doubleValue());

        // (set A4) direct inject
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A4");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+12); //last hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set B3)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(5);
        tmp->message->setPath(0,nextPhaseCounter+92);
        tmp->message->setPath(1,nextPhaseCounter+91);
        tmp->message->setPath(2,nextPhaseCounter+22);
        tmp->message->setPath(3,nextPhaseCounter+21);
        tmp->message->setPath(4,curPhaseCounter+22);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set C2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x31");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(9);
        tmp->message->setPath(0,nextPhaseCounter+93);
        tmp->message->setPath(1,nextPhaseCounter+92);
        tmp->message->setPath(2,nextPhaseCounter+95);
        tmp->message->setPath(3,nextPhaseCounter+94);
        tmp->message->setPath(4,nextPhaseCounter+32);
        tmp->message->setPath(5,nextPhaseCounter+31);
        tmp->message->setPath(6,curPhaseCounter+95);
        tmp->message->setPath(7,curPhaseCounter+94);
        tmp->message->setPath(8,curPhaseCounter+32);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set D1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set D1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x41");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(6);
        tmp->message->setPath(0,nextPhaseCounter+42);
        tmp->message->setPath(1,nextPhaseCounter+41);
        tmp->message->setPath(2,curPhaseCounter+93);
        tmp->message->setPath(3,curPhaseCounter+92);
        tmp->message->setPath(4,curPhaseCounter+91);
        tmp->message->setPath(5,curPhaseCounter+42);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

//round 5
        intervalStart += roundTime*(timeSlots->doubleValue());
        SimTime timeSyncR5=intervalStart;

        // (set B4) direct inject
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B4");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+22);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set C3)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x31");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,nextPhaseCounter+93);
        tmp->message->setPath(1,nextPhaseCounter+92);
        tmp->message->setPath(2,nextPhaseCounter+95);
        tmp->message->setPath(3,nextPhaseCounter+94);
        tmp->message->setPath(4,nextPhaseCounter+32);
        tmp->message->setPath(5,nextPhaseCounter+31);
        tmp->message->setPath(6,curPhaseCounter+32);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set D2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set D2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x41");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(5);
        tmp->message->setPath(0,nextPhaseCounter+42);
        tmp->message->setPath(1,nextPhaseCounter+41);
        tmp->message->setPath(2,curPhaseCounter+95);
        tmp->message->setPath(3,curPhaseCounter+94);
        tmp->message->setPath(4,curPhaseCounter+42);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set E1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set E1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x51");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(6);
        tmp->message->setPath(0,nextPhaseCounter+52);
        tmp->message->setPath(1,nextPhaseCounter+51);
        tmp->message->setPath(2,curPhaseCounter+93);
        tmp->message->setPath(3,curPhaseCounter+92);
        tmp->message->setPath(4,curPhaseCounter+91);
        tmp->message->setPath(5,curPhaseCounter+52);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);


//round 6
        intervalStart += roundTime*(timeSlots->doubleValue());

        // (set C4) direct inject
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C4");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x31");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+32);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set D3)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set D3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x41");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,nextPhaseCounter+42);
        tmp->message->setPath(1,nextPhaseCounter+41);
        tmp->message->setPath(2,curPhaseCounter+42);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set E2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set E2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x51");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(5);
        tmp->message->setPath(0,nextPhaseCounter+52);
        tmp->message->setPath(1,nextPhaseCounter+51);
        tmp->message->setPath(2,curPhaseCounter+95);
        tmp->message->setPath(3,curPhaseCounter+94);
        tmp->message->setPath(4,curPhaseCounter+52);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

//round 7
        intervalStart += roundTime*(timeSlots->doubleValue());

        // (set D4)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set D4");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x41");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+42);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

        // (set E3)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set E3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x51");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,nextPhaseCounter+52);
        tmp->message->setPath(1,nextPhaseCounter+51);
        tmp->message->setPath(2,curPhaseCounter+52);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

//round 8
        intervalStart += roundTime*(timeSlots->doubleValue());

        // (set E4)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set E4");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x51");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+52);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this now as selfmessage
        scheduleAt(intervalStart,tmp);

//inverse Phase follows
        //if (maxPhaseCounter-->0)
        //{
            char n=curPhaseName;
            curPhaseName=nextPhaseName;
            nextPhaseName=n;
            short int x=curPhaseCounter;
            curPhaseCounter=nextPhaseCounter;
            nextPhaseCounter=x;

            cMessage *selfNote = new cMessage("Start of Phase");
            selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
            selfNote->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
            selfNote->addPar("phaseCtrl");
            //the round number 5 of this phase is the first round of the next phase
            scheduleAt(timeSyncR5, selfNote);
        //}
    }
