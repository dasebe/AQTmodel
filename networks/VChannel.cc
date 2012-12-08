#include "VChannel.h"
Register_Class(VChannel);

VChannel::VChannel(const char *name) : cDelayChannel(name)
{
    numPackets = 0;
    txfinishtime = 0;
    delay = 0;
}

VChannel::~VChannel()
{
    //
}

void VChannel::initialize()
{
    cDelayChannel::initialize();
    delay = par("delay");
    delayDeviation = par("deviation");
    nextDelay = truncnormal(delay,delayDeviation);
}

void VChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    numPackets++;
    ev << "VChannel delivering " << numPackets << ". packet: " << msg->getName() << "\n";

    if (msg->isPacket())
    {
        result.duration = nextDelay;
        result.delay = nextDelay;
        txfinishtime = t + nextDelay;
        if(result.duration < simTime())
            ev << "negative duration";
        if(txfinishtime < simTime())
            ev << "negative duration";
        ev << "VChannel time: " << t.str() << " nextdelay: " << nextDelay << " txfinishtime: " <<txfinishtime;

        nextDelay = truncnormal(delay,delayDeviation);

        cPacket *pkt = (cPacket *)msg;
        simtime_t duration = pkt->getBitLength() / 10000;
        result.duration = duration;
        txfinishtime = t + duration;
    }
    else {
        txfinishtime = t;
    }
}


void VChannel::forceTransmissionFinishTime(simtime_t t)
{
    txfinishtime = t;
}
