package adversarialqueueing.node;

//
// This is the aggregate packet (OMNeT compound module) to create a network node.
// A network node consists of a Routing Module, an L2queue, and an App which represents the
// aggregate traffic of the subnets connected to that router.
//
module SourceRoutingNode
{
    parameters:
        int address;
        @display("i=misc/node_vs,gold;bgb=260,219,white");
    gates:
        inout port[];
    submodules:
        app: SourceRoutingApp {
            parameters:
                address = address;
                @display("p=94,27");
        }
        routing: SourceRouting {
            parameters:
                @display("p=94,97");
            gates:
                //NEEDS BE CHANGED for DiNodes
                in[sizeof(port)];
                out[sizeof(port)];
        }
        queue[sizeof(port)]: L2Queue {
            parameters:
                @display("p=34,167,row");
        }
    connections:
        routing.localOut --> app.in;
        routing.localIn <-- app.out;
        for i=0..sizeof(port)-1 {
            routing.out[i] --> queue[i].in;
            routing.in[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }
}


