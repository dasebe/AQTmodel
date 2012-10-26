#include "QueueListener.h"

QueueListener::QueueListener()
{
    // not anymore needed
}

QueueListener::~QueueListener()
{
    // not anymore needed
}

// would be easier to have separate objects for each queue... FIXME
void QueueListener::receiveSignal (cComponent *source, simsignal_t signalID, long l){
    //ev << "QueueListener Queue Length Signal received: " << l << endl;
    queuelength=l;
}

