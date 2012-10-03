#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifndef OMNETPP_H
#define OMNETPP_H
 #include <omnetpp.h>
#endif

#include "../messages/AdversarialInjectionMessage_m.h"
#include "../messages/QueueLengthRequest_m.h"
#include "../messages/AdvSchedMess.h"
#include "AdvancedAdversary.h"

/**
 * Generates and schedules injections for the nodes in the network.
 */
class BB : public AdvancedAdversary
{
  protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(BB);



void BB::injectInitialPackets()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    int initialSetSize=100; //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;
    maxPhaseCounter=2000;  //currently overall time fixed to simTime<=100s

//learn queue length
    //before the queue length later on can be queried -> need to create the listener objects

    cModule *targetModule = getParentModule()->getSubmodule("n1")->getSubmodule("routing");
    QueueLengthRequest *queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("n1");
    queueLenMsg->setOutAddress(12);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

    targetModule = getParentModule()->getSubmodule("m1")->getSubmodule("routing");
    queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("m1");
    queueLenMsg->setOutAddress(22);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

//  set where to start (left site of gadget)
    curPhaseName='n';
    curPhaseCounter=10;
    nextPhaseName='m';
    nextPhaseCounter=20;

//round 0
    // (initial packets)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime=0;
    tmp->packetCount=initialSetSize;
    tmp->message=new AdversarialInjectionMessage("init");
    tmp->atNode=new char[2];
    strcpy (tmp->atNode,"x1");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(1);
    tmp->message->setPath(0,curPhaseCounter+2);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);
}







    void BB::injectPhasePackets()
    {
        AdvSchedMess * tmp;
        //we assume we are indeed subscribed to the right queue! - no further consistency check!
        long roundTime=listener->queuelength[curPhaseCounter/10-1] + 1; //because one transmitted right away
        ev << "QL: "<< roundTime << endl;

//round 1
        timeSync = simTime(); //offset for first round = 0


        // (set X)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set X");
        tmp->atNode=new char[2];
        strcpy (tmp->atNode,"x1");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(4);
        tmp->message->setPath(0,nextPhaseCounter+2);
        tmp->message->setPath(1,nextPhaseCounter+1);
        tmp->message->setPath(2,curPhaseCounter+3);
        tmp->message->setPath(3,curPhaseCounter+2);//first hop
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
        tmp->message =  new AdversarialInjectionMessage("confinement");
        tmp->atNode=new char[2];
        strcpy (tmp->atNode,"x2");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+3);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        // (set B1)
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set Y");
        tmp->atNode=new char[2];
        strcpy (tmp->atNode,"x1");
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(4);
        tmp->message->setPath(0,nextPhaseCounter+2);
        tmp->message->setPath(1,nextPhaseCounter+1);
        tmp->message->setPath(2,curPhaseCounter+4);
        tmp->message->setPath(3,curPhaseCounter+2);//first hop
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
        tmp->message =  new AdversarialInjectionMessage("set Z");
        tmp->atNode=new char[2];
        strcpy (tmp->atNode,"x1");
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,nextPhaseCounter+2); //last hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        timeSync += roundTime*(timeSlots->doubleValue());

//inverse Phase follows
        if (maxPhaseCounter-->0)
        {
            char n=curPhaseName;
            curPhaseName=nextPhaseName;
            nextPhaseName=n;
            short int x=curPhaseCounter;
            curPhaseCounter=nextPhaseCounter;
            nextPhaseCounter=x;

            cMessage *selfNote = new cMessage("Start of Phase");
            selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
            tmp->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
            //the round number 5 of this phase is the first round of the next phase
            scheduleAt(timeSync, selfNote);
        }
    }
