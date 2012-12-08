
#include "ThruputMeteringChannel.h"

Register_Class(ThruputMeteringChannel);

ThruputMeteringChannel::ThruputMeteringChannel(const char *name) : cDatarateChannel(name)
{
}

ThruputMeteringChannel::~ThruputMeteringChannel()
{
}

void ThruputMeteringChannel::initialize()
{
    cDatarateChannel::initialize();
    meanDatarate = par("meanDatarate");
    stdDatarate = par("stdDatarate");
    cDatarateChannel::setDatarate(
            truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001);
}

void ThruputMeteringChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t, result);
    double nextDatarate = truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001;
    cDatarateChannel::setDatarate(nextDatarate);
    ev << "DR: " << nextDatarate;
}

