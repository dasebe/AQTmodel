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
class Diaz : public AdvancedAdversary
{
protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(Diaz);



void Diaz::injectInitialPackets()
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

    //stage 0
    //blue
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime=0;
    newInjection->packetCount=initialSetSize;
    newInjection->message=new AdversarialInjectionMessage("blue");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(4); //eo g f
    newInjection->message->setPath(0,nextPhaseCounter+1);
    newInjection->message->setPath(1,curPhaseCounter+6);
    newInjection->message->setPath(2,curPhaseCounter+5);
    newInjection->message->setPath(3,curPhaseCounter+2);
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);
}







void Diaz::injectPhasePackets()
{
    AdvSchedMess * newInjection;
    //we assume we are indeed subscribed to the right queue! - no further consistency check!
    long intervalLength;
    if(phaseCounter==0)
    {
        intervalLength=qlarray[curPhaseCounter/100-1]->queuelength + 1; //because one transmitted right away in first phase
    }
    else
    {
        intervalLength=qlarray[curPhaseCounter/100-1]->queuelength;
    }

    emit(measuredSetSizeSignal, intervalLength);
    ev << "QL: "<< intervalLength << endl;

    //check if we are running empty
    if(phaseCounter > 0 && intervalLength == 0)
    {
        return;
        ev << "Stopping as QL=0";
    }


    //stage 1
    intervalStart = simTime(); //offset for first interval = 0

    //green
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("green");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(8); //e0 f1 f e1 g' f'
    newInjection->message->setPath(0,curPhaseCounter+1);
    newInjection->message->setPath(1,nextPhaseCounter+6);
    newInjection->message->setPath(2,nextPhaseCounter+5);
    newInjection->message->setPath(3,nextPhaseCounter+2);
    newInjection->message->setPath(4,nextPhaseCounter+1);
    newInjection->message->setPath(5,curPhaseCounter+6);
    newInjection->message->setPath(6,curPhaseCounter+4);
    newInjection->message->setPath(7,curPhaseCounter+2);//first hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    //yellow
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("yellow");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x2");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,curPhaseCounter+5);
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);


    //stage 2
    intervalStart += intervalLength*(timeSlots->doubleValue());
    intervalLength = ceil(intervalLength*injectionRate);

    //orange
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("orange");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(7); //e0 f0 e1 g' f'
    newInjection->message->setPath(0,curPhaseCounter+1);
    newInjection->message->setPath(1,nextPhaseCounter+6);
    newInjection->message->setPath(2,nextPhaseCounter+5);
    newInjection->message->setPath(3,nextPhaseCounter+2);
    newInjection->message->setPath(4,nextPhaseCounter+1);
    newInjection->message->setPath(5,curPhaseCounter+3);
    newInjection->message->setPath(6,curPhaseCounter+2);//first hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    // purple
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("purple");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x6");
    newInjection->atNode[0]=curPhaseName;
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,nextPhaseCounter+1);//first hop
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(2);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);

    //stage 3
    intervalStart += intervalLength*(timeSlots->doubleValue());
    //old intervalLength = rs
    //new: (r+1/(1+r))rs
    intervalLength = ceil((injectionRate+1/(1+injectionRate))*intervalLength);

    //red
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    newInjection->packetCount=floor(intervalLength*injectionRate);
    newInjection->message =  new AdversarialInjectionMessage("red");
    newInjection->atNode=new char[2];
    strcpy (newInjection->atNode,"x1");
    newInjection->atNode[0]=nextPhaseName;
    newInjection->message->setPathArraySize(4);
    newInjection->message->setPath(0,curPhaseCounter+1);
    newInjection->message->setPath(1,nextPhaseCounter+6);
    newInjection->message->setPath(2,nextPhaseCounter+5);
    newInjection->message->setPath(3,nextPhaseCounter+2); //last hop
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
