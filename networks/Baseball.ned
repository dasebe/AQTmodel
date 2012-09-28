
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.BBAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network Baseball
{
    @display("bgb=688,504");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        w0: SourceRoutingNode {
            @display("p=128,96");
            address = 111;
        }
        f1: SourceRoutingNode {
            @display("p=91,284");
            address = 121;
        }
        f2: SourceRoutingNode {
            @display("p=170,284");
            address = 122;
        }
        v1: SourceRoutingNode {
            @display("p=128,434");
            address = 131;
        }
        w1: SourceRoutingNode {
            @display("p=481,434");
            address = 211;
        }
        g2: SourceRoutingNode {
            @display("p=418,284");
            address = 222;
        }
        g1: SourceRoutingNode {
            @display("p=526,284");
            address = 221;
        }
        v0: SourceRoutingNode {
            @display("p=481,96");
            address = 231;
        }
        adversary: BBAdversary {
            @display("p=620,63");
        }
    connections:

        w0.port++ <--> C <--> f1.port++;
        f1.port++ <--> C <--> v1.port++;
        v1.port++ <--> C <--> w1.port++;
        w1.port++ <--> C <--> g1.port++;
        w1.port++ <--> C <--> g2.port++;
        g2.port++ <--> C <--> v0.port++;
        g1.port++ <--> C <--> v0.port++;
        v0.port++ <--> C <--> w0.port++;
        w0.port++ <--> C <--> f2.port++;
        f2.port++ <--> C <--> v1.port++;
}

