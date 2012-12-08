//========================================================================
//  CDATARATECHANNEL.CC - part of
//
//                 OMNeT++/OMNEST
//              Discrete System Simulation in C++
//
//========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2008 Andras Varga
  Copyright (C) 2006-2008 OpenSim Ltd.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include "GaussianChannel.h"
#include "cmessage.h"
#include "cmodule.h"
#include "cenvir.h"
#include "random.h"
#include "distrib.h"
#include "csimulation.h"
#include "globals.h"
#include "cgate.h"
#include "cexception.h"
#include "ctimestampedvalue.h"

#ifdef WITH_PARSIM
#include "ccommbuffer.h"
#endif

USING_NAMESPACE

using std::ostream;

Register_Class(GaussianChannel);

simsignal_t GaussianChannel::channelBusySignal;
simsignal_t GaussianChannel::messageSentSignal;
simsignal_t GaussianChannel::messageDiscardedSignal;

GaussianChannel::GaussianChannel(const char *name) : cChannel(name)
{
    txfinishtime = 0;
    delay = 0;
    datarate = 0;
    ber = 0;
    per = 0;
}

GaussianChannel::~GaussianChannel()
{
}

GaussianChannel *GaussianChannel::create(const char *name)
{
    return dynamic_cast<GaussianChannel *>(cChannelType::getDatarateChannelType()->create(name));
}

std::string GaussianChannel::info() const
{
    return cChannel::info();
}

void GaussianChannel::initialize()
{
    channelBusySignal = registerSignal("channelBusy");
    messageSentSignal = registerSignal("messageSent");
    messageDiscardedSignal = registerSignal("messageDiscarded");

    emit(channelBusySignal, 0);
}

void GaussianChannel::rereadPars()
{
    delay = par("delay");
    datarate = par("datarate");
    ber = par("ber");
    per = par("per");

    if (delay < 0)
        throw cRuntimeError(this, "negative delay %s", SIMTIME_STR(delay));
    if (datarate < 0)
        throw cRuntimeError(this, "negative datarate %g", datarate);
    if (ber < 0 || ber > 1)
        throw cRuntimeError(this, "wrong bit error rate %g", ber);
    if (per < 0 || per > 1)
        throw cRuntimeError(this, "wrong packet error rate %g", per);

    setFlag(FL_DELAY_NONZERO, delay!=0);
    setFlag(FL_DATARATE_NONZERO, datarate!=0);
    setFlag(FL_BER_NONZERO, ber!=0);
    setFlag(FL_PER_NONZERO, per!=0);
}

void GaussianChannel::handleParameterChange(const char *)
{
    rereadPars();
}

void GaussianChannel::setDelay(double d)
{
    par("delay").setDoubleValue(d);
}

void GaussianChannel::setDatarate(double d)
{
    par("datarate").setDoubleValue(d);
}

void GaussianChannel::setBitErrorRate(double d)
{
    par("ber").setDoubleValue(d);
}

void GaussianChannel::setPacketErrorRate(double d)
{
    par("per").setDoubleValue(d);
}

void GaussianChannel::setDisabled(bool d)
{
    par("disabled").setBoolValue(d);
}

simtime_t GaussianChannel::calculateDuration(cMessage *msg) const
{
    if ((flags & FL_DATARATE_NONZERO) && msg->isPacket())
        return ((cPacket *)msg)->getBitLength() / datarate;
    else
        return SIMTIME_ZERO;
}

void GaussianChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    // if channel is disabled, signal that message should be deleted
    if (flags & FL_ISDISABLED)
    {
        result.discard = true;
        cTimestampedValue tmp(t, msg);
        emit(messageDiscardedSignal, &tmp);
        return;
    }

    // datarate modeling
    if ((flags & FL_DATARATE_NONZERO) && msg->isPacket())
    {
        cPacket *pkt = (cPacket *)msg;
        simtime_t duration = pkt->getBitLength() / datarate;
        result.duration = duration;
        txfinishtime = t + duration;
    }
    else {
        txfinishtime = t;
    }

    // propagation delay modeling
    result.delay = delay;

    // bit error modeling
    if ((flags & (FL_BER_NONZERO | FL_PER_NONZERO)) && msg->isPacket())
    {
        cPacket *pkt = (cPacket *)msg;
        if (flags & FL_BER_NONZERO)
            if (dblrand() < 1.0 - pow(1.0-ber, (double)pkt->getBitLength()))
                pkt->setBitError(true);
        if (flags & FL_PER_NONZERO)
            if (dblrand() < per)
                pkt->setBitError(true);
    }

    // emit signals
    if (mayHaveListeners(messageSentSignal))
    {
        MessageSentSignalValue tmp(t, msg, &result);
        emit(messageSentSignal, &tmp);
    }
    if (mayHaveListeners(channelBusySignal))
    {
        cTimestampedValue tmp(t, 1L);
        emit(channelBusySignal, &tmp);

        tmp.timestamp = txfinishtime; tmp.l = 0L;
        emit(channelBusySignal, &tmp);
    }
}

void GaussianChannel::forceTransmissionFinishTime(simtime_t t)
{
    //TODO record this into the eventlog so that it can be visualized in the sequence chart
    txfinishtime = t;
}

