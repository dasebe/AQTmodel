#ifndef VCHANNEL_H
#define VCHANNEL_H

#include <omnetpp.h>
#include <distrib.h>

class VChannel : public cDelayChannel
{
protected:
    int numPackets;
    simtime_t delay; //already defined in delay channel: this is the mean delay
    simtime_t nextDelay; //delay the next packet traversing this link will encounter
    simtime_t delayDeviation; //standard deviation of the Gaussian distributed RV of the delay
    simtime_t txfinishtime;

public:
    /**
     * Constructor.
     */
    explicit VChannel(const char *name = NULL);

    /**
     * Destructor.
     */
    virtual ~VChannel();

    /**
     * Add parameters and initialize random delay
     */
    virtual void initialize();

    /**
     * Adds randomization to a link traversal according to configuration
     */
    virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);

    /**
     * This channel sets a duration to an arriving message!
     */
    virtual bool isTransmissionChannel() const {return true;}
    virtual void forceTransmissionFinishTime(simtime_t t);
};

#endif
