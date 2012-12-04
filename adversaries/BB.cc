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

    //define adversarial injections
    int initialSetSize=par("initialSetSize"); //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;

    //learn queue length
    //before the queue length later on can be queried -> need to create the listener objects

    requestQueueLength("n1", 12);
    requestQueueLength("m1", 22);

    //use strings as node names, and integers for addresses
    // set where to start (left site of gadget)
    curPhaseName='n';
    curPhaseCounter=10;
    nextPhaseName='m';
    nextPhaseCounter=20;

    //interval 0
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
    long intervalLength=qlarray[curPhaseCounter/10-1]->queuelength + 1; //because one transmitted currently
    emit(measuredSetSizeSignal, intervalLength);
    ev << "QL: "<< intervalLength << endl;

    //interval 1
    timeSync = simTime(); //offset for first interval = 0


    // (set X)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    tmp->packetCount=floor(intervalLength*injectionRate);
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



    //interval 2
    timeSync += intervalLength*(timeSlots->doubleValue());
    intervalLength = ceil(intervalLength*injectionRate);

    // (set confinement)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    //this should be of size B*r/(1+r)
    //also ceil here as it's going to make it more efficient and still valid
    tmp->packetCount=ceil((intervalLength*injectionRate)/(1+injectionRate));
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

    // (set Y)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    tmp->packetCount=floor(intervalLength*injectionRate);
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

    //interval 3
    timeSync += intervalLength*(timeSlots->doubleValue());
    intervalLength = ceil(intervalLength*injectionRate);

    // (set A3) direct inject
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    tmp->packetCount=floor(intervalLength*injectionRate);
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

    timeSync += intervalLength*(timeSlots->doubleValue());

    //inverse Phase follows
    char n=curPhaseName;
    curPhaseName=nextPhaseName;
    nextPhaseName=n;
    short int x=curPhaseCounter;
    curPhaseCounter=nextPhaseCounter;
    nextPhaseCounter=x;

    cMessage *selfNote = new cMessage("Start of Phase");
    selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
    tmp->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //the interval number 5 of this phase is the first interval of the next phase
    scheduleAt(timeSync, selfNote);
}
