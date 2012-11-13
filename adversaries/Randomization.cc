#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <omnetpp.h>
#include <cdataratechannel.h>
#include <distrib.h>

class Randomization : public cSimpleModule
{
protected:
    cMessage *selfNote;
    double meandelay;
    double stddelay;
    SimTime timeslot;
    void initialize();
    void changeAllDelays();
    void handleMessage(cMessage *msg);
};

Define_Module(Randomization);



void Randomization::initialize()
{

    timeslot = par("sendIaTime");

    cPar *mdt = &par("meandelay");
    meandelay = mdt->doubleValue();
    cPar *sd = &par("stddelay");
    stddelay = sd->doubleValue();

    selfNote = new cMessage("Change Delay");
    selfNote->setKind(110);
    selfNote->setSchedulingPriority(0);
    scheduleAt(simTime(), selfNote);
}

void Randomization::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        changeAllDelays();
        scheduleAt(simTime()+timeslot, selfNote);
        return;
    }
}

void Randomization::changeAllDelays()
{
    cModule *modp = getParentModule();
    for (cModule::SubmoduleIterator i(modp); !i.end(); i++)
    {
        cModule *submodp = i();
        for (cModule::GateIterator i(submodp); !i.end(); i++)
        {
            cGate *gate = i();
            cChannel *gchannel = gate->getChannel();
            if(gchannel != NULL)
            {
                cDatarateChannel *drchannel = check_and_cast<cDatarateChannel *>(gchannel);
                drchannel->setDelay(truncnormal(meandelay,stddelay));
            }
        }
    }
}
