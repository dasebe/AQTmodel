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
    AdvSchedMess * newInjection;

    //learn queue length
    //before the queue length later on can be queried -> need to create the listener objects
    requestQueueLength("C", 1);
    requestQueueLength("B", 4);

    isNewPhase = true;

    //interval 0
    // (initial packets)
    newInjection = new AdvSchedMess;
    newInjection->interInjectionTime=0;
    newInjection->packetCount=initialSetSize;
    newInjection->message=new AdversarialInjectionMessage("init");
    newInjection->atNode = new char[1];
    strcpy(newInjection->atNode, "C" );
    newInjection->message->setPathArraySize(1);
    newInjection->message->setPath(0,1);
    newInjection->message->setKind(101);
    newInjection->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(intervalStart,newInjection);
}







void APlusMinor::injectPhasePackets()
{
    AdvSchedMess * newInjection;

    if(isNewPhase)
    {
        //we assume we are indeed subscribed to the right queue! - no further consistency check!
        long intervalLength=qlarray[0]->queuelength + 1; //because one transmitted currently
        emit(measuredSetSizeSignal, intervalLength);
        ev << "QL: "<< intervalLength << endl;

        //interval [t0,t1]
        intervalStart = simTime(); //offset = 0
        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        newInjection->packetCount = floor(intervalLength*injectionRate);
        newInjection->message =  new AdversarialInjectionMessage("set S1");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "C" );
        newInjection->message->setPathArraySize(4);
        newInjection->message->setPath(0,4);
        newInjection->message->setPath(1,3);
        newInjection->message->setPath(2,21);
        newInjection->message->setPath(3,1);//first hop
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        //interval [t1,t2] confinement
        intervalStart += intervalLength*(timeSlots->doubleValue());
        intervalLength = ceil(intervalLength*injectionRate);

        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        //this should be of size B*r/(1+r)
        //also ceil here as it's going to make it more efficient and still valid
        newInjection->packetCount = ceil((intervalLength*injectionRate)/(1+injectionRate));
        newInjection->message =  new AdversarialInjectionMessage("confinement");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "D" );
        newInjection->message->setPathArraySize(1);
        newInjection->message->setPath(0,3);
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        //interval [t1,t2]
        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        newInjection->packetCount = floor(intervalLength*injectionRate);
        newInjection->message =  new AdversarialInjectionMessage("set S2");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "C" );
        newInjection->message->setPathArraySize(4);
        newInjection->message->setPath(0,4);
        newInjection->message->setPath(1,3);
        newInjection->message->setPath(2,22);
        newInjection->message->setPath(3,1);//first hop
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        //interval [t2,t3]
        intervalStart += intervalLength*(timeSlots->doubleValue());
        intervalLength = ceil(intervalLength*injectionRate);

        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        newInjection->packetCount = floor(intervalLength*injectionRate);
        newInjection->message =  new AdversarialInjectionMessage("set S3");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "B" );
        newInjection->message->setPathArraySize(1);
        newInjection->message->setPath(0,4); //last hop
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        // + 3 time steps because set S2 is two hops away
        intervalStart += (intervalLength+3)*(timeSlots->doubleValue());
    }
    else
    {
        //interval [t3,t4]
        //Loss Transport [Weinard06] depends on the actual set size -> query for it
        long basicIntervalTime = qlarray[1]->queuelength + 1;

        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        newInjection->packetCount = floor(basicIntervalTime*injectionRate);
        newInjection->message =  new AdversarialInjectionMessage("set S4");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "B" );
        newInjection->message->setPathArraySize(3);
        newInjection->message->setPath(0,1);
        newInjection->message->setPath(1,5);
        newInjection->message->setPath(2,4);//first hop
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        //interval  [t4,t5]
        // + 1 time step because the distance is one time step
        intervalStart += (basicIntervalTime+1)*(timeSlots->doubleValue());
        basicIntervalTime = ceil(basicIntervalTime*injectionRate);

        newInjection = new AdvSchedMess;
        newInjection->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        newInjection->packetCount = floor(basicIntervalTime*injectionRate);
        newInjection->message =  new AdversarialInjectionMessage("set S5");
        newInjection->atNode = new char[1];
        strcpy(newInjection->atNode, "C" );
        newInjection->message->setPathArraySize(1);
        newInjection->message->setPath(0,1);
        newInjection->message->setKind(101);
        newInjection->setSchedulingPriority(2);
        //schedule this at timesync as selfmessage
        scheduleAt(intervalStart,newInjection);

        intervalStart += basicIntervalTime*(timeSlots->doubleValue());
    }


    isNewPhase = !isNewPhase;

    //schedule next Phase
    cMessage *selfNote = new cMessage("Start of Phase");
    selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //the interval number 5 of this phase is the first interval of the next phase
    scheduleAt(intervalStart, selfNote);
}
