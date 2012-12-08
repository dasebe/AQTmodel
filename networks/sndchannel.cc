//========================================================================
//  CDELAYCHANNEL.CC - part of
//
//                 OMNeT++/OMNEST
//              Discrete System Simulation in C++
//
//   Member functions of
//    cDelayChannel : channel class
//
//========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2008 Andras Varga
  Copyright (C) 2006-2008 OpenSim Ltd.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include "sndchannel.h"
#include "cmessage.h"
#include "cenvir.h"
#include "globals.h"
#include "cgate.h"
#include "cexception.h"
#include "ctimestampedvalue.h"

#ifdef WITH_PARSIM
#include "ccommbuffer.h"
#endif

USING_NAMESPACE

using std::ostream;

Register_Class(sndChannel);

simsignal_t sndChannel::messageSentSignal;
simsignal_t sndChannel::messageDiscardedSignal;

sndChannel *sndChannel::create(const char *name)
{
    return dynamic_cast<sndChannel *>(cChannelType::getDelayChannelType()->create(name));
}

void sndChannel::initialize()
{
    messageSentSignal = registerSignal("messageSent");
    messageDiscardedSignal = registerSignal("messageDiscarded");
}

void sndChannel::rereadPars()
{
    delay = par("delay");
    if (delay < 0)
        throw cRuntimeError(this, "negative delay %s", SIMTIME_STR(delay));
    setFlag(FL_DELAY_NONZERO, delay!=0);
}

void sndChannel::handleParameterChange(const char *)
{
    rereadPars();
}

void sndChannel::setDelay(double d)
{
    par("delay").setDoubleValue(d);
}

void sndChannel::setDisabled(bool d)
{
    par("disabled").setBoolValue(d);
}

void sndChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    // if channel is disabled, signal that message should be deleted
    if (flags & FL_ISDISABLED)
    {
        result.discard = true;
        cTimestampedValue tmp(t, msg);
        emit(messageDiscardedSignal, &tmp);
        return;
    }

    // propagation delay modeling
    result.delay = delay;

    // emit signals
    if (mayHaveListeners(messageSentSignal))
    {
        MessageSentSignalValue tmp(t, msg, &result);
        emit(messageSentSignal, &tmp);
    }
}

