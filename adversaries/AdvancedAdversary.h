
#ifndef ADVANCEDADVERSARY_H_
#define ADVANCEDADVERSARY_H_

#include <vector>
#include <omnetpp.h>
#include "AdversarialInjectionMessage_m.h"


/**
 * message kinds:
 * 0-99:  adversarial rounds (injection round)
 * 101:   adversarial command
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

    struct Inj
    {
        long packetCount;   // [start,stop] time range for injection
        const char* atNode;         // where to initially deploy the packets upon injection
        double interInjectionTime;  // 1/injectionRate - will directly go into the offset for scheduleAt events
        AdversarialInjectionMessage *message; //adversarial injection command to be send to nodes
        int packetNHops;
        int *packetPath;    // path injected together with the packets (possibly of unkown length)
    };

    // state
    Inj *injections;
    cMessage *selfNote; //self-messaging //actually not needed as class attribute // TODO: clean-up
    long injectionCount;
    char curPhaseName;
    short int  curPhaseCounter;


    /**
     * listener class to learn about queue lengths
     * Needed because cListener is only "A do-nothing implementation of cIListener, suitable as a base class for other listeners."
     * and we need to "redefine one or more of the overloaded receiveSignal() methods"
     */

    //TODO unclean -> should be somewhere else
    class QueueListener : public cListener {
        public:
            long queuelength;
            QueueListener(){queuelength=0;}
            void receiveSignal (cComponent *source, simsignal_t signalID, long l){
                ev << "QueueListener Queue Length Signal received: " << l << endl;
                queuelength=l;
                source->getFullPath();
            }
    };

    QueueListener *listener;
    long queueLen;


    // signals for statistics (e.g.)
    simsignal_t injectedPackets;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void injectInitialPackets(){};
    virtual void injectPhasePackets(){};
    virtual void receiveSignal(cComponent *src, simsignal_t id, long l);
};

Define_Module(AdvancedAdversary);



#endif /* ADVANCEDADVERSARY_H_ */
