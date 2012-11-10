//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>


/**
 * Point-to-point interface module. While one frame is transmitted,
 * additional frames get queued up; see NED file for more info.
 */
class L2Queue : public cSimpleModule
{
  private:
    long frameCapacity;

    cQueue queue;
    cMessage *endTransmissionEvent;

    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;
    simsignal_t dropSignal;
    simsignal_t txBytesSignal;
    simsignal_t rxBytesSignal;

  public:
    L2Queue();
    virtual ~L2Queue();

    virtual void dispose();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void startTransmitting(cMessage *msg);

    virtual void displayStatus(bool isBusy);
};

Define_Module(L2Queue);
