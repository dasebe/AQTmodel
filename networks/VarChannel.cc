#include <omnetpp.h>

class VarChannel : public cDelayChannel
{
  private:
    int numPackets;
    SimTime nextDelay;
    SimTime channelMeanDelay;
  protected:
    virtual void initialize();
    virtual void rereadPars();
    virtual bool isTransmissionChannel() const {return false;}
    virtual simtime_t calculateDuration(cMessage *msg);
    virtual simtime_t getTransmissionFinishTime();
    virtual void forceTransmissionFinishTime(simtime_t t);
    virtual double getNominalDatarate() const {return 0;}; //similar to delaychannel
    virtual void processMessage(cMessage *msg, simtime_t at, result_t& result);
    virtual void finish();
};

Define_Channel(VarChannel);


void VarChannel::initialize()
{
    ev << "Initializing VarChannel " << getFullPath() << "\n";
    numPackets = 0;
    nextDelay = truncnormal(channelMeanDelay,0.0001);
    rereadPars();
}

void VarChannel::rereadPars()
{
    channelMeanDelay = par("channelMeanDelay");
}

simtime_t VarChannel::calculateDuration(cMessage *msg)
{
    return nextDelay;
}


void VarChannel::processMessage(cMessage *msg, simtime_t at, result_t& result)
{
    numPackets++;
    ev << "VarChannel delivering msg: " << msg->getName() << "\n";

    // propagation delay modeling
    result.duration = nextDelay;
    nextDelay = truncnormal(channelMeanDelay,0.0001);
}

void VarChannel::finish()
{
    ev << "varChannel finishing, msgs: " << numPackets << "\n";
}

simtime_t VarChannel::getTransmissionFinishTime()
{
    return nextDelay;
}

void VarChannel::forceTransmissionFinishTime(simtime_t t)
{
    //TODO record this into the eventlog so that it can be visualized in the sequence chart
    nextDelay = t;
}
