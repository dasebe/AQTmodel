#include "QueueListener.h"

QueueListener::QueueListener()
{
    queueCount=2;
    queuelength[0]=0;
    queuelength[1]=0;
}

QueueListener::~QueueListener()
{
    //
}

// would be easier to have separate objects for each queue... FIXME
void QueueListener::receiveSignal (cComponent *source, simsignal_t signalID, long l){
    //ev << "QueueListener Queue Length Signal received: " << l << endl;
    for (int i=0;i<queueCount;i++)
    {
        if(subscribedComponents[i]==source)
            queuelength[i]=l;
    }
}

