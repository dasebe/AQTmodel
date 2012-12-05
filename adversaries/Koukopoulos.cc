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
class Koukopoulos : public AdvancedAdversary
{
protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(Koukopoulos);



void Koukopoulos::injectInitialPackets()
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

    // TBD
}







void Koukopoulos::injectPhasePackets()
{
    AdvSchedMess * newInjection;
    //we assume we are indeed subscribed to the right queue! - no further consistency check!
    long intervalLength=qlarray[curPhaseCounter/10-1]->queuelength + 1; //because one transmitted currently
    emit(measuredSetSizeSignal, intervalLength);
    ev << "QL: "<< intervalLength << endl;

    // TBD


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
