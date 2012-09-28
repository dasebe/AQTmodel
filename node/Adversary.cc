#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <vector>
#include <omnetpp.h>
#include "AdversarialInjectionMessage_m.h"


/**
 * Generates traffic for the network.
 */
class Adversary : public cSimpleModule
{
  private:
    // configuration
    cPar *sendIATime;

    // state
    cMessage *selfNote; //self-messaging
    int round;   // adversarial round (overall state of adversary)
    int messagesPerRound[4];
    int confinementCounter;
    long injectionCount;

    // signals
            //none as yet

  public:
    Adversary();
    virtual ~Adversary();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Adversary);


Adversary::Adversary()
{
    selfNote = NULL;
}

Adversary::~Adversary()
{
    cancelAndDelete(selfNote);
}

void Adversary::initialize()
{
    sendIATime = &par("sendIaTime");

    round = 0;
    injectionCount = 0;
    confinementCounter = 500;//47; //currently only needed for control of timimg for confinement

    messagesPerRound[0] = 1000;
    messagesPerRound[1] = 1000;//90;
    messagesPerRound[2] = 1000;//81;
    messagesPerRound[3] = 1000;//73;

    WATCH(round);

    //generate initial packet to start own state machine
    selfNote = new cMessage("round0");
    scheduleAt(simTime(), selfNote);
}



void Adversary::handleMessage(cMessage *msg)
{
    //still spaghetti form of programming --> needs review!


    //////////////////////////////////////////////////////////////

    if (strcmp (msg->getFullName(),"round0")==0)
    {
        round = 0;

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("v0")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(1);
        m->setPath(0,111);//first hop

        injectionCount++;
        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injecting round 0");

        if(--messagesPerRound[0] > 0) //messagesPerRound first decreased (as we just sent one) then checked whether anything remains for this round
        {
            //stay in round 1
            scheduleAt(simTime(), new cMessage("round0"));
        }
        else
        {
            //now proceed to round 2
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round1"));
        }
    }

    //////////////////////////////////////////////////////////////

    else if (strcmp (msg->getFullName(),"round1")==0)
    {
        round = 1;

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("v0")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(4);
        m->setPath(0,211); //last hop
        m->setPath(1,131);
        m->setPath(2,121);
        m->setPath(3,111);//first hop

        injectionCount++;
        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injection command round 1...");

        if(--messagesPerRound[1] > 0) //messagesPerRound first decreased (as we just sent one) then checked whether anything remains for this round
        {
            //stay in round 1
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round1"));
        }
        else
        {
            //now proceed to round 2
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round2"));
        }
    }

    //////////////////////////////////////////////////////////////

    else if (strcmp (msg->getFullName(),"round2")==0)
    {
        round = 2;

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("v0")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(4);
        m->setPath(0,211); //last hop
        m->setPath(1,131);
        m->setPath(2,122);
        m->setPath(3,111);//first hop

        injectionCount++;
        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injection command round 2...");



        //confinement

        if(confinementCounter-- > 0)
        {
            targetModule = getParentModule()->getSubmodule("w0")->getSubmodule("app");
            //std::vector<const char *> a = targetModule->getGateNames();

            //create an injection message to be send to the first hop of the new injection
            m = new AdversarialInjectionMessage("injection");
            m->setPathArraySize(1);
            m->setPath(0,121);
            injectionCount++;
            sendDirect(m, targetModule, "adversaryControl");
            if (ev.isGUI()) getParentModule()->bubble("injection command round 2...");
        }


        if(--messagesPerRound[2] > 0)
        {
            //stay in round 1
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round2"));
        }
        else
        {
            //now proceed to round 2
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round3"));
        }
    }

    //////////////////////////////////////////////////////////////


    else if (strcmp (msg->getFullName(),"round3")==0)
    {
        round = 3;

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("v1")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(1);
        m->setPath(0,211); //last hop

        injectionCount++;
        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injection command round 1...");

        if(--messagesPerRound[3] > 0) //messagesPerRound first decreased (as we just sent one) then checked whether anything remains for this round
        {
            //stay in round 1
            scheduleAt(simTime() + sendIATime->doubleValue(), new cMessage("round3"));
        }

    }
}

