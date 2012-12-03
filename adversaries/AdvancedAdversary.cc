// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#ifndef ADVANCEDADVERSARY_H
#define ADVANCEDADVERSARY_H
 #include "AdvancedAdversary.h"
#endif

/**
 * Framework for definitions of adversaries
 *
 * To create an adversary subclass from this one, an reimplement
 *    virtual void injectInitialPackets(){};
 *    virtual void injectRoundPackets(){};
 * to reflect the actions done by the adversary
 */

AdvancedAdversary::AdvancedAdversary(){}

AdvancedAdversary::~AdvancedAdversary()
{
    //delete all the queue listeners
    for(unsigned int i=0; i < this->qlarray.size();i++)
        delete(this->qlarray[i]);
    //delete(&(this->qlarray));
}

void AdvancedAdversary::initialize()
{
    timeSlots = &par("sendIaTime");
    bufferSize = par("frameCapacity");
    injectionRate = par("injectionRate");
    injectionCount = 0;
    timeSync = simTime(); // == 0 (as we init!)
    maxPhaseCounter=0;
    WATCH(injectionCount);

    injectedPackets = registerSignal("injectedPackets");
    measuredSetSizeSignal = registerSignal("measuredSetSize");

    injectInitialPackets();
    /**
     * InjectRoundPackets cannot be called right away, as it needs information
     * about the network state.
     * Because of this it has to be called at the end after all initial injection
     * _took_ place -> we create a special selfmessage for this.
     */

    cMessage *selfNote = new cMessage("Start of Phase");
    selfNote->setKind(102); //this means that the first entry of the injection struct shall be started by this message
    selfNote->setSchedulingPriority(7); //higher means lower priority, normal packets get 4 (initial injection 1, other injection 2)
    selfNote->addPar("phaseCtrl");
    //when to start this phase
    scheduleAt(simTime(), selfNote);
}


/*
 * Helper function to simplify setting a queue listener for links in the network.
 * As a queue is specific for some particular link, a queue listener is set by giving
 * a target node and the address of another adjacent node, so that the routing table
 * can be used to lookup the corresponding port.
 */
void AdvancedAdversary::requestQueueLength(const char* atNode, int outAddress)
{
    cModule *targetModule = getParentModule()->getSubmodule(atNode)->getSubmodule("routing");
    QueueLengthRequest *queueLenMsg = new QueueLengthRequest("getGate");
    queueLenMsg->setModuleName(atNode);
    queueLenMsg->setOutAddress(outAddress);
    queueLenMsg->setKind(103);
    sendDirect(queueLenMsg, targetModule, "adversaryControl");
}



void AdvancedAdversary::handleMessage(cMessage *msg)
{
    //set up a queue listener
    if (msg->getKind()==103)
    {
        QueueLengthRequest *pk = check_and_cast<QueueLengthRequest *>(msg);
        //subscribe new queue length listener

        //safe old array, into new one of bigger size
        //only done once per adversary - fine

        QueueListener * ql = new QueueListener();
        this->qlarray.push_back(ql);

        cModule *queue = getParentModule()->getSubmodule(pk->getModuleName())->
                getSubmodule("queue",pk->getGateID());

        //subscribe listener to component
        queue->subscribe("qlen", ql);
        cancelAndDelete(msg);
        return;
    }

    //a new phase start
    if (msg->getKind()==102)
    {
        //now that this Phase has started the adversary can take measurements and do injections
        injectPhasePackets();
        cancelAndDelete(msg);
        return;
    }


    //internal scheduling message
    if(msg->isSelfMessage()) //scheduling of injections is all done by selfMessaging
    {
        //don't catch exception - assume it's fine
        AdvSchedMess *aSMess = check_and_cast<AdvSchedMess *>(msg);

        //parentModule is complete network
        //then select the vertice/node
        //then select the corresponding app (to which we will deliver the message by avoiding the queue...)
        cModule *targetModule = getParentModule()->getSubmodule(aSMess->atNode)->getSubmodule("app");

        //we already have a message defined in our Inj struct

        if (aSMess->packetCount-- > 0) //only send a message if remaining
        {

            emit(injectedPackets, ++injectionCount);
            //send duplicate of message, as we won't be the owner after it has been passed to targetModule
            sendDirect(aSMess->message->dup(), targetModule, "adversaryControl");

            if (ev.isGUI()) getParentModule()->bubble("inject");

            EV << "INJECT:     at " << aSMess->atNode << "  set " << msg->getName() << "  remain " << aSMess->packetCount << endl;

            scheduleAt(simTime() + aSMess->interInjectionTime, aSMess);
        }
        else
        {
            //then this scheduler is done
            cancelAndDelete(aSMess->message);
            cancelAndDelete(msg);
        }

    }

}

