#ifndef _ADVERSARIALSCHEDULINGMESSAGE_M_H_
#define _ADVERSARIALSCHEDULINGMESSAGE_M_H_

#include <omnetpp.h>
#include <AdversarialInjectionMessage_m.h>

//
// This cMessage subtype is used to sync and schedule the adversary internally via the exchange of selfmessages (events)
//

class AdvSchedMess : public ::cMessage
{
public:
        long packetCount;   // [start,stop] time range for injection
        char* atNode;         // where to initially deploy the packets upon injection
        double interInjectionTime;  // 1/injectionRate - will directly go into the offset for scheduleAt events
        AdversarialInjectionMessage *message; //adversarial injection command to be send to nodes
        int packetNHops;
        int *packetPath;    // path injected together with the packets (possibly of unkown length)
};


#endif // _ADVERSARIALSCHEDULINGMESSAGE_M_H_
