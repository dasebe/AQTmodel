#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "AdversarialInjectionMessage_m.h"
#include "AdvancedAdversary.h"

/**
 * Generates and schedules injections for the nodes in the network.
 */
class CE7Advanced : public AdvancedAdversary
{
  protected:
    void injectInitialPackets();
    void injectPhasePackets();

    void concat3(char& first,const char * second, char * buffer);
    void concat3(const char * second, char * buffer){};
    void concat3(char& first,const char * second){};
    void concat3(char& first, char * buffer){};

};

Define_Module(CE7Advanced);



void CE7Advanced::injectInitialPackets()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    WATCH(injectionCount);

    //define adversarial injections
    noInjs = 3+3+3+3+3; //3initial sets, 3x3injections + 3 direct injects
    injections = (Inj*) malloc(noInjs*sizeof(Inj));
    int initialSetSize=10; //in time steps (not simulationTime!!)
    Inj * tmp;
    int tmpi=0;

//learn queue length
    //before the queue length later on can be queried -> need to create the listener objects

    //init listener (even at first time want to check whether subscribed)
    listener = new QueueListener();

    cModule *targetModule = getParentModule()->getSubmodule("n11")->getSubmodule("routing");
    cMessage *queueLenMsg = new cMessage("queue length n11-n12?");
    (*queueLenMsg).addPar("queueLenQ");
    (*queueLenMsg).par("queueLenQ").setLongValue(112);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");






//round 0
    // (initial packets A)
    tmp = &injections[tmpi];
    tmp->interInjectionTime = 0;
    tmp->interInjectionTime = 0;
    tmp->packetCount=initialSetSize;
    tmp->message =  new AdversarialInjectionMessage("initial set A0");
    tmp->atNode = "n11";
    tmp->message->setPathArraySize(1);
    tmp->message->setPath(0,112);
    tmp->message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: A0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


//round 1
    timeSync = simTime(); //offset for first round = 0


//round 2
    timeSync += initialSetSize*(timeSlots->doubleValue());

    // (initial packets B)
    tmp = &injections[tmpi];
    tmp->interInjectionTime = 0;
    tmp->packetCount= initialSetSize;
    tmp->message =  new AdversarialInjectionMessage("initial set B0");
    tmp->atNode = "n21";
    tmp->message->setPathArraySize(3);
    tmp->message->setPath(0,192);
    tmp->message->setPath(1,191);
    tmp->message->setPath(2,122);
    tmp->message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: B0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(timeSync, selfNote);


//round 3
    timeSync += initialSetSize*(timeSlots->doubleValue());

    // (initial packets C)
    tmp = &injections[tmpi];
    tmp->interInjectionTime = 0;
    tmp->packetCount=initialSetSize;
    tmp->message =  new AdversarialInjectionMessage("initial set C0");
    tmp->atNode = "n31";
    tmp->message->setPathArraySize(5);
    tmp->message->setPath(0,193);
    tmp->message->setPath(1,192);
    tmp->message->setPath(2,195);
    tmp->message->setPath(3,194);
    tmp->message->setPath(4,132);
    tmp->message->setKind(101);
    //schedule event message for this injection class
    selfNote = new cMessage("S: C0");
    selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(1); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    //when to start this phase
    scheduleAt(timeSync, selfNote);

    curPhaseName='n';
    curPhaseCounter=100;
}







    void CE7Advanced::injectPhasePackets()
    {
        Inj * tmp;
        int tmpi=3;
        //we assume we are not subscribed to the right queue! - no further consistency check!
        long roundTime=listener->queuelength + 1; //because one transmitted right away
        ev << "got queue length: "<< roundTime << endl;
        char * atNodeName = new char[3];

//round 1
        timeSync = simTime(); //offset for first round = 0


        // (set A1)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A1");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"11");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(6);
        tmp->message->setPath(0,curPhaseCounter+14);
        tmp->message->setPath(1,curPhaseCounter+13);
        tmp->message->setPath(2,curPhaseCounter+93);
        tmp->message->setPath(3,curPhaseCounter+92);
        tmp->message->setPath(4,curPhaseCounter+91);
        tmp->message->setPath(5,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);



//round 2
        timeSync += roundTime*(timeSlots->doubleValue());

        // (set A2)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A2");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"11");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(5);
        tmp->message->setPath(0,curPhaseCounter+14);
        tmp->message->setPath(1,curPhaseCounter+13);
        tmp->message->setPath(2,curPhaseCounter+95);
        tmp->message->setPath(3,curPhaseCounter+94);
        tmp->message->setPath(4,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B1)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B1");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"21");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(9);
        tmp->message->setPath(0,curPhaseCounter+97);//last hop
        tmp->message->setPath(1,curPhaseCounter+96);
        tmp->message->setPath(2,curPhaseCounter+25);
        tmp->message->setPath(3,curPhaseCounter+24);
        tmp->message->setPath(4,curPhaseCounter+23);
        tmp->message->setPath(5,curPhaseCounter+93);
        tmp->message->setPath(6,curPhaseCounter+92);
        tmp->message->setPath(7,curPhaseCounter+91);
        tmp->message->setPath(8,curPhaseCounter+22);//first hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 3
        timeSync += roundTime*(timeSlots->doubleValue());


        // (set A3)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A3");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"11");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(3);
        tmp->message->setPath(0,curPhaseCounter+14); //last hop
        tmp->message->setPath(1,curPhaseCounter+13);
        tmp->message->setPath(2,curPhaseCounter+12);//first hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B2)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B2");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"21");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(8);
        tmp->message->setPath(0,curPhaseCounter+97);
        tmp->message->setPath(1,curPhaseCounter+96);
        tmp->message->setPath(2,curPhaseCounter+25);
        tmp->message->setPath(3,curPhaseCounter+24);
        tmp->message->setPath(4,curPhaseCounter+23);
        tmp->message->setPath(5,curPhaseCounter+95);
        tmp->message->setPath(6,curPhaseCounter+94);
        tmp->message->setPath(7,curPhaseCounter+22);
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C1)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C1");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"31");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(10);
        tmp->message->setPath(0,curPhaseCounter+98);
        tmp->message->setPath(1,curPhaseCounter+97);
        tmp->message->setPath(2,curPhaseCounter+99);
        tmp->message->setPath(3,curPhaseCounter+35);
        tmp->message->setPath(4,curPhaseCounter+34);
        tmp->message->setPath(5,curPhaseCounter+33);
        tmp->message->setPath(6,curPhaseCounter+93);
        tmp->message->setPath(7,curPhaseCounter+92);
        tmp->message->setPath(8,curPhaseCounter+91);
        tmp->message->setPath(9,curPhaseCounter+32);
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C1");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 4
        timeSync += roundTime*(timeSlots->doubleValue());

        // (set A4) direct inject
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set A4");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"13");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+14); //last hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: A4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set B3)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B3");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"21");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(6);
        tmp->message->setPath(0,curPhaseCounter+97);
        tmp->message->setPath(1,curPhaseCounter+96);
        tmp->message->setPath(2,curPhaseCounter+25);
        tmp->message->setPath(3,curPhaseCounter+24);
        tmp->message->setPath(4,curPhaseCounter+23);
        tmp->message->setPath(5,curPhaseCounter+22);
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C2)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C2");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"31");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(9);
        tmp->message->setPath(0,curPhaseCounter+98);
        tmp->message->setPath(1,curPhaseCounter+97);
        tmp->message->setPath(2,curPhaseCounter+99);
        tmp->message->setPath(3,curPhaseCounter+35);
        tmp->message->setPath(4,curPhaseCounter+34);
        tmp->message->setPath(5,curPhaseCounter+33);
        tmp->message->setPath(6,curPhaseCounter+95);
        tmp->message->setPath(7,curPhaseCounter+94);
        tmp->message->setPath(8,curPhaseCounter+32);
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C2");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//round 5
        timeSync += roundTime*(timeSlots->doubleValue());
        SimTime timeSyncR5=timeSync;

        // (set B4) direct inject
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set B4");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"23");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+24); //last hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: B4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

        // (set C3)
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C3");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"31");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(7);
        tmp->message->setPath(0,curPhaseCounter+98);
        tmp->message->setPath(1,curPhaseCounter+97);
        tmp->message->setPath(2,curPhaseCounter+99);
        tmp->message->setPath(3,curPhaseCounter+35);
        tmp->message->setPath(4,curPhaseCounter+34);
        tmp->message->setPath(5,curPhaseCounter+33);
        tmp->message->setPath(6,curPhaseCounter+32);
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C3");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);

//round 6
        timeSync += roundTime*(timeSlots->doubleValue());

        // (set C4) direct inject
        tmp = &injections[tmpi];
        tmp->interInjectionTime = (timeSlots->doubleValue())/injectionRate;
        tmp->packetCount=floor(roundTime*injectionRate);
        tmp->message =  new AdversarialInjectionMessage("set C4");
        atNodeName=new char[3];
        atNodeName[0]=curPhaseName;
        strcat(atNodeName,"33");
        tmp->atNode = atNodeName;
        tmp->message->setPathArraySize(1);
        tmp->message->setPath(0,curPhaseCounter+34); //last hop
        tmp->message->setKind(101);
        //schedule event message for this injection class
        selfNote = new cMessage("S: C4");
        selfNote->setKind(tmpi++); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(2); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        //when to start this phase
        scheduleAt(timeSync, selfNote);


//inverse Phase follows
        if (curPhaseCounter==1)
        {
            curPhaseName='m';
            curPhaseCounter=200;
        }
        else
        {
            curPhaseName='n';
            curPhaseCounter=100;
        }

        selfNote = new cMessage("Start of Phase");
        selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
        selfNote->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
        selfNote->addPar("phaseCtrl");
        //the round number 5 of this phase is the first round of the next phase
        scheduleAt(timeSyncR5, selfNote);

    }

    void concat3(char& first,const char * second, char * buffer)
    {
        buffer[0]=first;
        buffer[1]=second[0];
        buffer[2]=second[1];
    }

