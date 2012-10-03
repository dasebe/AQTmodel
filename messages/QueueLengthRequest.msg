
//
// With messages of this type requests to subscribe to a queue's length
// are prepared.
//
packet QueueLengthRequest {
    string moduleName;  //node name where routing and queue are located
    int	gateID;         //(response) gate in routing where the requested queue is located 
    int outAddress;     //(request) address of next hop on whose link the queue is located
}
