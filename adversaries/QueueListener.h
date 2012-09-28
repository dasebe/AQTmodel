#ifndef OMNETPP_H
#define OMNETPP_H
 #include <omnetpp.h>
#endif


    /**
     * listener class to learn about queue lengths
     * Needed because cListener is only "A do-nothing implementation of cIListener, suitable as a base class for other listeners."
     * and we need to "redefine one or more of the overloaded receiveSignal() methods"
     */

class QueueListener : public cListener {
        public:
            int queueCount;
            long queuelength[2];
            cComponent * subscribedComponents[2]; //TODO use case only 2 subscriptions - works for now (else #include <vector>)

            QueueListener();
            ~QueueListener();
            void receiveSignal(cComponent *src, simsignal_t id, long l);
};

