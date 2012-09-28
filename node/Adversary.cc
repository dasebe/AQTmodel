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

    WATCH(round);

    //generate initial packet to start own state machine
    selfNote = new cMessage("round1");
    scheduleAt(simTime(), selfNote);
}



void Adversary::handleMessage(cMessage *msg)
{
    if (strcmp (msg->getFullName(),"round1")==0)
    {
        //round 1

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("w0")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(6);
        m->setPath(0,231);//last hop
        m->setPath(1,222);
        m->setPath(2,211);
        m->setPath(3,131);
        m->setPath(4,121);
        m->setPath(5,111);//first hop

        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injection command round 1...");

            //now proceed to round 2
        scheduleAt(sendIATime->doubleValue(), new cMessage("round2"));
    }


    else if (strcmp (msg->getFullName(),"round2")==0)
    {
        //round 2

        //parentModule is DanielBB (main module)
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule("w0")->getSubmodule("app");
        //std::vector<const char *> a = targetModule->getGateNames();

        //create an injection message to be send to the first hop of the new injection
        AdversarialInjectionMessage *m = new AdversarialInjectionMessage("injection");
        m->setPathArraySize(6);
        m->setPath(0,231);//last hop
        m->setPath(1,222);
        m->setPath(2,211);
        m->setPath(3,131);
        m->setPath(4,122);
        m->setPath(5,111);//first hop

        sendDirect(m, targetModule, "adversaryControl");
        if (ev.isGUI()) getParentModule()->bubble("injection command round 1...");

    }
}

