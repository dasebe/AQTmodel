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
class APlusMinor : public AdvancedAdversary
{
protected:
    bool isNewPhase;
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(APlusMinor);



void APlusMinor::injectInitialPackets()
{

    //define adversarial injections
    int initialSetSize=par("initialSetSize"); //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;

    //learn queue length
    //before the queue length later on can be queried -> need to create the listener objects
    requestQueueLength("C", 1);
    requestQueueLength("B", 4);

    isNewPhase = true;

    //interval 0
    // (initial packets)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime=0;
    tmp->packetCount=initialSetSize;
    tmp->message=new AdversarialInjectionMessage("init");
    tmp->atNode="C";
    tmp->message->setPathArraySize(1);
    tmp->message->setPath(0,1);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);
}







void APlusMinor::injectPhasePackets()
{
    AdvSchedMess * tmp;

    if(isNewPhase)
    {
        //we assume we are indeed subscribed to the right queue! - no further consistency check!
        long basicIntervalTime=qlarray[0]->queuelength + 1; //because one transmitted currently
        ev << "QL: "<< basicIntervalTime << endl;

        //interval 1
        timeSync = simTime(); //offset for first interval = 0
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(basicIntervalTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set S1");
        tmp->atNode="C";
        tmp->message->setPathArraySize(4);
        tmp->message->setPath(0,4);
        tmp->message->setPath(1,3);
        tmp->message->setPath(2,21);
        tmp->message->setPath(3,1);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        //interval 2
        timeSync += basicIntervalTime*(timeSlots->doubleValue());
        basicIntervalTime = basicIntervalTime*injectionRate;

        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        //this should be of size B*r/(1+r)
        //also ceil here as it's going to make it more efficient and still valid
        tmp->packetCount=ceil((basicIntervalTime*injectionRate)/(1+injectionRate));
        tmp->message =  new AdversarialInjectionMessage("confinement");
        tmp->atNode="D";
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,3);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(basicIntervalTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set S2");
        tmp->atNode="C";
        tmp->message->setPathArraySize(4);
        tmp->message->setPath(0,4);
        tmp->message->setPath(1,3);
        tmp->message->setPath(2,22);
        tmp->message->setPath(3,1);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        //interval 3
        timeSync += basicIntervalTime*(timeSlots->doubleValue());
        basicIntervalTime = basicIntervalTime*injectionRate;

        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(basicIntervalTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set S3");
        tmp->atNode="B";
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,4); //last hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        // + 3 time steps because set S2 is two hops away
        timeSync += (basicIntervalTime+3)*(timeSlots->doubleValue());
    }
    else
    {
        //interval 4
        //Loss Transport [Weinard06] depends on the actual set size -> query for it
        long basicIntervalTime=qlarray[1]->queuelength + 1;

        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(basicIntervalTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set S4");
        tmp->atNode="B";
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,1);
        tmp->message->setPath(1,5);
        tmp->message->setPath(2,4);//first hop
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        //interval 5
        // + 1 time step because the distance is one time step
        timeSync += (basicIntervalTime+1)*(timeSlots->doubleValue());
        basicIntervalTime = basicIntervalTime*injectionRate;

        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(basicIntervalTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set S5");
        tmp->atNode="C";
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,1);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);

        timeSync += basicIntervalTime*(timeSlots->doubleValue());
    }


    isNewPhase = !isNewPhase;

    //schedule next Phase
    cMessage *selfNote = new cMessage("Start of Phase");
    selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
    tmp->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //the interval number 5 of this phase is the first interval of the next phase
    scheduleAt(timeSync, selfNote);
}
