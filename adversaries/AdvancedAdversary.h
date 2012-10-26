
#ifndef ADVANCEDADVERSARY_H_
#define ADVANCEDADVERSARY_H_

#include <vector>

#ifndef OMNETPP_H
#define OMNETPP_H
 #include <omnetpp.h>
#endif

#ifndef ADVSCHEDMESS_H
#define ADVSCHEDMESS_H
#include "../messages/AdvSchedMess.h"
#endif

#include "../messages/AdversarialInjectionMessage_m.h"
#include "../messages/QueueLengthRequest_m.h"
#include "QueueListener.h"

/**
 * message kinds:
 * 0-99:  adversarial rounds (injection round)
 * 101:   adversarial command
 * 102:   start of phase command
 * 103:   queueRequest message
 */

/**
 * message scheduling priorities:
 * 0:  default
 * 0:   queue length requests
 * 1:   initial set injection scheduling
 * 2:   normal injection scheduling
 * 4:   injection commands
 * 6:   network packets
 * 7:   phase start
 */

/**
 * routing:
 * based on shortest path!
 * source routing: give list (array) of nodes to visit in reverse order via setPath command to packets!
 * => possible to leave out intermediate hops - not done here for clarity
 */

/**
 * Framework for definitions of adversaries
 *
 * To create an adversary subclass from this one, an reimplement
 *    virtual void injectInitialPackets(){};
 *    virtual void injectRoundPackets(){};
 * to reflect the actions done by the adversary
 */
class AdvancedAdversary : public cSimpleModule
{
public:
    AdvancedAdversary();
    virtual ~AdvancedAdversary();

protected:
    // configuration
    cPar *timeSlots;
    long bufferSize;
    double injectionRate;
    SimTime timeSync;
    int noInjs;
    long injectionCount;
    char curPhaseName;
    short int  curPhaseCounter;
    char nextPhaseName;
    short int  nextPhaseCounter;
    long maxPhaseCounter;

    std::vector<QueueListener*> qlarray;
    long queueLen;

    // signals for statistics (e.g.)
    simsignal_t injectedPackets;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void injectInitialPackets(){};
    virtual void injectPhasePackets(){};
};

Define_Module(AdvancedAdversary);



#endif /* ADVANCEDADVERSARY_H_ */
