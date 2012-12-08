#ifndef __INET_THRUPUTMETERINGCHANNEL_H
#define __INET_THRUPUTMETERINGCHANNEL_H

#include <omnetpp.h>
#include <distrib.h>

class ThruputMeteringChannel : public cDatarateChannel
{
  protected:
    int meanDatarate;
    int stdDatarate;
  public:
    explicit ThruputMeteringChannel(const char *name = NULL);
    virtual ~ThruputMeteringChannel();
    virtual void initialize();
    virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
};

#endif
