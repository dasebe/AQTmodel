
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.CE3Adversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;


//
// This is the basic omnet network description of CE3.
//
network CE3half
{
    @display("bgb=409,634");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        a1: SourceRoutingNode {
            @display("p=216,122");
            address = 11;
        }
        a2: SourceRoutingNode {
            @display("p=216,377");
            address = 12;
        }
        b2: SourceRoutingNode {
            @display("p=345,377");
            address = 22;
        }
        m1: SourceRoutingNode {
            @display("p=283,212");
            address = 91;
        }
        b1: SourceRoutingNode {
            @display("p=345,122");
            address = 21;
        }
        adversary: CE3Adversary {
            @display("p=56,212");
        }
        a0: SourceRoutingNode {
            @display("p=216,21");
            address = 10;
        }
        b0: SourceRoutingNode {
            @display("p=345,21");
            address = 20;
        }
        m2: SourceRoutingNode {
            @display("p=283,295");
            address = 92;
        }
        a3: SourceRoutingNode {
            @display("p=216,493");
            address = 13;
        }
        b3: SourceRoutingNode {
            @display("p=345,493");
            address = 23;
        }
    connections:

        m1.port++ <--> C <--> b1.port++;
        a1.port++ <--> C <--> a0.port++;
        b0.port++ <--> C <--> b1.port++;
        a1.port++ <--> C <--> m1.port++;
        m1.port++ <--> C <--> m2.port++;
        m2.port++ <--> C <--> a2.port++;
        m2.port++ <--> C <--> b2.port++;
        a1.port++ <--> C <--> a2.port++;
        b1.port++ <--> C <--> b2.port++;
        b2.port++ <--> C <--> b3.port++;
        a2.port++ <--> C <--> a3.port++;
}

