#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#ifndef OMNETPP_H
#define OMNETPP_H
#include <omnetpp.h>
#endif

#include "../messages/AdversarialInjectionMessage_m.h"
#include "../messages/QueueLengthRequest_m.h"
#include "../messages/AdvSchedMess.h"
#include "AdvancedAdversary.h"

/**
 * Generates and schedules injections for the nodes in the network.
 */
class Koukopoulos : public AdvancedAdversary
{
protected:
    void injectInitialPackets();
    void injectPhasePackets();
};

Define_Module(Koukopoulos);



void Koukopoulos::injectInitialPackets()
{

}





void Koukopoulos::injectPhasePackets()
{

}
