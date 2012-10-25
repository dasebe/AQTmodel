#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <math.h>

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
class Lotker1 : public AdvancedAdversary
{
protected:
    void injectInitialPackets();
    void injectPhasePackets();

    char thirdPhaseName;
    short int  thirdPhaseCounter;
    //lotker parameter
    const static int lengthn = 8;
};

Define_Module(Lotker1);



void Lotker1::injectInitialPackets()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    int initialSetSize=1000; //in time steps (not simulationTime!!)
    AdvSchedMess * tmp;
    maxPhaseCounter=200;  //currently overall time fixed to simTime<=100s

    //learn initial queue length
    //before the queue length later on can be queried -> need to create the listener objects
    cModule *targetModule = getParentModule()->getSubmodule("a01")->getSubmodule("routing");
    QueueLengthRequest *queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("a01");
    queueLenMsg->setOutAddress(102);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

    targetModule = getParentModule()->getSubmodule("b01")->getSubmodule("routing");
    queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("b01");
    queueLenMsg->setOutAddress(202);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");

    targetModule = getParentModule()->getSubmodule("c01")->getSubmodule("routing");
    queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName("c01");
    queueLenMsg->setOutAddress(302);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");



    //  set where to start (left site of gadget)
    curPhaseName='a';
    curPhaseCounter=100;
    nextPhaseName='b';
    nextPhaseCounter=200;
    thirdPhaseName='c';
    thirdPhaseCounter=300;

//round 0 create C(S,F_1)
    // (1) + (2)
    // inject in each e_i (lower path) one packet and the remainder into the last one
    for (int i=1; i<lengthn; i++)
    {
        tmp = new AdvSchedMess;
        tmp->interInjectionTime=0;
        tmp->packetCount=1;
        tmp->message=new AdversarialInjectionMessage("(1) init");
        tmp->atNode=new char[3];
        sprintf(tmp->atNode,"x2%d",i);
        tmp->atNode[0]=curPhaseName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,thirdPhaseCounter+02);
        tmp->message->setPath(1,thirdPhaseCounter+01);
        tmp->message->setPath(2,nextPhaseCounter+20+lengthn);
        tmp->message->setPath(3,nextPhaseCounter+21);
        tmp->message->setPath(4,nextPhaseCounter+02);
        tmp->message->setPath(5,nextPhaseCounter+01);
        tmp->message->setPath(6,curPhaseCounter+20+lengthn);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(1);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync,tmp);
    }
    tmp = new AdvSchedMess;
    tmp->interInjectionTime=0;
    tmp->packetCount=initialSetSize-lengthn+1;
    tmp->message=new AdversarialInjectionMessage("(1) init");
    tmp->atNode=new char[3];
    sprintf(tmp->atNode,"x2%d",lengthn);
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(6);
    tmp->message->setPath(0,thirdPhaseCounter+02);
    tmp->message->setPath(1,thirdPhaseCounter+01);
    tmp->message->setPath(2,nextPhaseCounter+20+lengthn);
    tmp->message->setPath(3,nextPhaseCounter+21);
    tmp->message->setPath(4,nextPhaseCounter+02);
    tmp->message->setPath(5,nextPhaseCounter+01);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);


    // (3)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime=0;
    tmp->packetCount=initialSetSize;
    tmp->message=new AdversarialInjectionMessage("(3) init");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x01");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(8);
    tmp->message->setPath(0,thirdPhaseCounter+02);
    tmp->message->setPath(1,thirdPhaseCounter+01);
    tmp->message->setPath(2,nextPhaseCounter+10+lengthn);
    tmp->message->setPath(3,nextPhaseCounter+11);
    tmp->message->setPath(4,nextPhaseCounter+02);
    tmp->message->setPath(5,nextPhaseCounter+01);
    tmp->message->setPath(6,curPhaseCounter+10+lengthn);
    tmp->message->setPath(7,curPhaseCounter+12);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);
}







void Lotker1::injectPhasePackets()
{
    AdvSchedMess * tmp;
    //we assume we are indeed subscribed to the right queue! - no further consistency check!
    long roundTime=listener->queuelength[curPhaseCounter/100-1] + 1; //because one transmitted right away
    ev << "QL: "<< roundTime << endl;

    //round 1
    timeSync = simTime(); //offset for first round = 0


    // (single-edge confinement)

    for (int i=1; i<=lengthn; i++)
    {
        double Ri = (1-injectionRate)/(1-pow(injectionRate,i));
        double ti = (2*roundTime)/(injectionRate + Ri);
        //for this node, inject in [i,i+ti]
        //hence scheduleAt timeSync + i*timeslot and send ceil(ti) packets at rate r
        tmp = new AdvSchedMess;
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=ceil(ti);
        tmp->message=new AdversarialInjectionMessage("confinement");
        tmp->atNode=new char[3];
        sprintf(tmp->atNode,"x2%d",i);
        tmp->atNode[0]=nextPhaseName;
        tmp->message->setPathArraySize(1);
        if (i==lengthn)
            tmp->message->setPath(0,thirdPhaseCounter+1);
        else
            tmp->message->setPath(0,nextPhaseCounter+20+i+1);
        tmp->message->setKind(101);
        tmp->setSchedulingPriority(1);
        //schedule this at timesync as selfmessage
        scheduleAt(timeSync+(timeSlots->doubleValue())*i,tmp);
    }


    //actual new injections:    new (3)
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    tmp->packetCount= floor(roundTime*injectionRate);
    tmp->message=new AdversarialInjectionMessage("(3) long way");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x01");
    tmp->atNode[0]=curPhaseName;
    tmp->message->setPathArraySize(9);
    tmp->message->setPath(0,thirdPhaseCounter+02);
    tmp->message->setPath(1,thirdPhaseCounter+01);
    tmp->message->setPath(2,nextPhaseCounter+10+lengthn);
    tmp->message->setPath(3,nextPhaseCounter+11);
    tmp->message->setPath(4,nextPhaseCounter+02);
    tmp->message->setPath(5,nextPhaseCounter+01);
    tmp->message->setPath(6,curPhaseCounter+10+lengthn);
    tmp->message->setPath(7,curPhaseCounter+11);
    tmp->message->setPath(8,curPhaseCounter+02);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);




    timeSync += (timeSlots->doubleValue())*(roundTime+lengthn+1);

    //actual new injections: X   new (4)
    double Rn = (1-injectionRate)/(1-pow(injectionRate,lengthn));
    int X = floor(2*roundTime*(1-Rn)-injectionRate*roundTime+lengthn);
    tmp = new AdvSchedMess;
    tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
    tmp->packetCount= X;
    tmp->message=new AdversarialInjectionMessage("X, (4)");
    tmp->atNode=new char[3];
    strcpy (tmp->atNode,"x01");
    tmp->atNode[0]=nextPhaseName;
    tmp->message->setPathArraySize(5);
    tmp->message->setPath(0,thirdPhaseCounter+02);
    tmp->message->setPath(1,thirdPhaseCounter+01);
    tmp->message->setPath(2,nextPhaseCounter+10+lengthn);
    tmp->message->setPath(3,nextPhaseCounter+11);
    tmp->message->setPath(4,nextPhaseCounter+02);
    tmp->message->setKind(101);
    tmp->setSchedulingPriority(1);
    //schedule this at timesync as selfmessage
    scheduleAt(timeSync,tmp);

    //cancelAndDelete()
}
