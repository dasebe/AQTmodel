//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


package adversarialqueueing.node;

//
// This is the aggregate packet (omnet compound module) to create a network node.
// A network node consists of a Routing Module, an L2queue, and an App which represents the
// aggregate traffic of the subnets connected to that router.
//
module SourceRoutingNode
{
    parameters:
        int address;
        string appType;
        @display("i=misc/node_vs,gold");
    gates:
        inout port[];
    submodules:
        app: <appType> like IApp {
            parameters:
                address = address;
                @display("p=140,60");
        }
        routing: SourceRouting {
            parameters:
                @display("p=140,130");
            gates:
                //NEEDS BE CHANGED for DiNodes
                in[sizeof(port)];
                out[sizeof(port)];
        }
        queue[sizeof(port)]: L2Queue {
            parameters:
                @display("p=80,200,row");
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


