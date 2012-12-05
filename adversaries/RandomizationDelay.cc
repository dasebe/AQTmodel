#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <omnetpp.h>
#include <cdataratechannel.h>
#include <distrib.h>

class RandomizationDelay : public cSimpleModule
{
protected:
    cMessage *selfNote;
    double meandelay;
    SimTime timeslot;
    void initialize();
    void changeAllDelays();
    void handleMessage(cMessage *msg);
};

Define_Module(RandomizationDelay);



void RandomizationDelay::initialize()
{

    timeslot = par("sendIaTime");

    cPar *mdt = &par("meandelay");
    meandelay = mdt->doubleValue();

    selfNote = new cMessage("Change Delay");
    selfNote->setKind(110);
    selfNote->setSchedulingPriority(0);
    scheduleAt(simTime(), selfNote);
}

void RandomizationDelay::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        changeAllDelays();
        scheduleAt(simTime()+timeslot, selfNote);
        return;
    }
}

void RandomizationDelay::changeAllDelays()
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
                //drchannel->setDatarate(truncnormal(meandelay,stdrate));
            }
        }
    }
}
