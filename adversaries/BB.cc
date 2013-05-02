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
    AdvSchedMess * newInjection;

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
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime=0;
    newInjection->packetCount=initialSetSize;
    newInjection->message=new AdversarialInjectionMessage("init");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,curPhaseCounter+2);
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);
}







void BB::injectPhasePackets()
{
    AdvSchedMess * newInjection;
    //we assume we are indeed subscribed to the right queue! - no further consistency check!
    long intervalLength;
    if(phaseCounter==0)
    {
        intervalLength=qlarray[curPhaseCounter/10-1]->queuelength + 1; //because one transmitted right away in first phase
    }
    else
    {
        intervalLength=qlarray[curPhaseCounter/10-1]->queuelength;
    }

    emit(measuredSetSizeSignal, intervalLength);
    ev << "QL: "<< intervalLength << endl;

    //check if we are running empty
    if(phaseCounter > 0 && intervalLength == 0)
    {
        return;
        ev << "Stopping as QL=0";
    }


    //interval 1
    intervalStart = simTime(); //offset for first interval = 0


    // (set X)
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("set X");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(4);
    newInjection->message->setPath(0,nextPhaseCounter+2);
    newInjection->message->setPath(1,nextPhaseCounter+1);
    newInjection->message->setPath(2,curPhaseCounter+3);
    newInjection->message->setPath(3,curPhaseCounter+2);//first hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);



    //interval 2
    intervalStart += intervalLength*(timeSlots->doubleValue());
    intervalLength = ceil(intervalLength*injectionRate);

    // (set confinement)
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    //this should be of size B*r/(1+r)
    //also ceil here as it's going to make it more efficient and still valid
    newInjection->packetCount=ceil((intervalLength*injectionRate)/(1+injectionRate));
    newInjection->message =  new AdversarialInjectionMessage("confinement");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x2");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,curPhaseCounter+3);
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    // (set Y)
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("set Y");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(4);
    newInjection->message->setPath(0,nextPhaseCounter+2);
    newInjection->message->setPath(1,nextPhaseCounter+1);
    newInjection->message->setPath(2,curPhaseCounter+4);
    newInjection->message->setPath(3,curPhaseCounter+2);//first hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    //interval 3
    intervalStart += intervalLength*(timeSlots->doubleValue());
    intervalLength = ceil(intervalLength*injectionRate);

    // (set A3) direct inject
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("set Z");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=nextPhaseName;
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,nextPhaseCounter+2); //last hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    intervalStart += intervalLength*(timeSlots->doubleValue());

    //inverse Phase follows
    char n=curPhaseName;
    curPhaseName=nextPhaseName;
    nextPhaseName=n;
    short int x=curPhaseCounter;
    curPhaseCounter=nextPhaseCounter;
    nextPhaseCounter=x;

    cMessage *selfNote = new cMessage("Start of Phase");
    selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //the interval number 5 of this phase is the first interval of the next phase
    scheduleAt(intervalStart, selfNote);
}
