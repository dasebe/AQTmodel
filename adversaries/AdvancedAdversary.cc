// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "AdvancedAdversary.h"

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
    //TODO where's the clean-up
    delete(listener);
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

    //define adversarial injections
    noInjs = 0;
    //injections = (Inj*) malloc(noInjs*sizeof(Inj)); must be overwritten later

    //init queue length listener
    listener = new QueueListener();

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


    injectedPackets = registerSignal("injectedPackets");
}



void AdvancedAdversary::handleMessage(cMessage *msg)
{
    //TODO architecture not clean: should use msgKind to distinguish different messages, and Params to hand over the injection command.

    if (msg->hasPar("qlenGate"))
    {
        //subscribe queue length listener -> stupid solution: FIXME

        //limitation: only two subscriptions!
        if (listener->getSubscribeCount()>1) {
            return; //hitting limitation
        }
        //store component
        listener->subscribedComponents[listener->getSubscribeCount()]=
                getParentModule()->
                getSubmodule(msg->getName())->
                getSubmodule("queue",msg->par("qlenGate").longValue());
        //subscribe listener to component
        listener->subscribedComponents[listener->getSubscribeCount()]->
                subscribe("qlen", listener);
        cancelAndDelete(msg);
        return;
    }

    if (msg->hasPar("phaseCtrl"))
    {
        //now that this Phase has started the adversary can take measurements and do injections
        injectPhasePackets();
        cancelAndDelete(msg);
        return;
    }





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

