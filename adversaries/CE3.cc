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
class CE3 : public AdvancedAdversary
{
  protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(CE3);



void CE3::injectInitialPackets()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    int initialSetSize=par("initialSetSize"); //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;
    maxPhaseCounter=200;  //currently overall time fixed to simTime<=100s

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
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);


//round 1
    timeSync = simTime(); //offset for first round = 0


//round 2
    timeSync += initialSetSize*(timeSlots->doubleValue());

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
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);

}







    void CE3::injectPhasePackets()
    {
        AdvSchedMess * tmp;
        //we assume we are indeed subscribed to the right queue! - no further consistency check!
        long roundTime=qlarray[curPhaseCounter/100-1]->queuelength + 1; //because one transmitted right away
        ev << "QL: "<< roundTime << endl;

//round 1
        timeSync = simTime(); //offset for first round = 0


        // (set A1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,nextPhaseCounter+92);
        tmp->message->setPath(1,nextPhaseCounter+91);
        tmp->message->setPath(2,nextPhaseCounter+12);
        tmp->message->setPath(3,nextPhaseCounter+11);
        tmp->message->setPath(4,curPhaseCounter+92);
        tmp->message->setPath(5,curPhaseCounter+91);
        tmp->message->setPath(6,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);



//round 2
        timeSync += roundTime*(timeSlots->doubleValue());

        // (set A2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A2");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,nextPhaseCounter+12);
        tmp->message->setPath(1,nextPhaseCounter+11);
        tmp->message->setPath(2,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        // (set B1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B1");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,nextPhaseCounter+92);//last hop
        tmp->message->setPath(1,nextPhaseCounter+91);
        tmp->message->setPath(2,nextPhaseCounter+22);
        tmp->message->setPath(3,nextPhaseCounter+21);
        tmp->message->setPath(4,curPhaseCounter+92);
        tmp->message->setPath(5,curPhaseCounter+91);
        tmp->message->setPath(6,curPhaseCounter+22);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

//round 3
        timeSync += roundTime*(timeSlots->doubleValue());

        // (set A3) direct inject
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x11");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+12); //last hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        // (set B2)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B2");
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
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

//round 4
        timeSync += roundTime*(timeSlots->doubleValue());
        SimTime timeSyncR5=timeSync;

        // (set B3) direct inject
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B3");
        tmp->atNode=new char[3];
        strcpy (tmp->atNode,"x21");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+22);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

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
