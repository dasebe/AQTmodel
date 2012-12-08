#include <omnetpp.h>

class VarChannel : public cDelayChannel//cChannel
{
  private:
    int numPackets;
    SimTime channelMeanDelay;
    SimTime nextDelay;
  protected:
    void initialize();
    void rereadPars();
    bool isTransmissionChannel() const {return false;}
    simtime_t calculateDuration(cMessage *msg);
    simtime_t getTransmissionFinishTime();
    void forceTransmissionFinishTime(simtime_t t);
    double getNominalDatarate() const {return 0;}; //similar to delaychannel
    void processMessage(cMessage *msg, simtime_t at, result_t& result);
    void finish();
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
    channelMeanDelay = 0.001;//par("channelMeanDelay");
}

simtime_t VarChannel::calculateDuration(cMessage *msg)
{
    return nextDelay;
}

simtime_t VarChannel::getTransmissionFinishTime()
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


void VarChannel::forceTransmissionFinishTime(simtime_t t)
{
    //TODO record this into the eventlog so that it can be visualized in the sequence chart
    nextDelay = t;
}
