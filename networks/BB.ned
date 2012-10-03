
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network BB
{
    parameters:
        string adType;
        @display("bgb=328,408,white");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:
        adversary: <adType> like AdvancedAdversary {
            @display("p=135,77");
        }
        n1: SourceRoutingNode {
            @display("p=240,40");
            address = 11;
        }
        n2: SourceRoutingNode {
            @display("p=66,40");
            address = 12;
        }
        n3: SourceRoutingNode {
            @display("p=29,213");
            address = 13;
        }
        n4: SourceRoutingNode {
            @display("p=108,213");
            address = 14;
        }
        m1: SourceRoutingNode {
            @display("p=66,363");
            address = 21;
        }
        m2: SourceRoutingNode {
            @display("p=240,363");
            address = 22;
        }
        m4: SourceRoutingNode {
            @display("p=177,213");
            address = 24;
        }
        m3: SourceRoutingNode {
            @display("p=285,213");
            address = 23;
        }
    connections:

        n2.port++ <--> C <--> n3.port++;
        n3.port++ <--> C <--> m1.port++;
        m1.port++ <--> C <--> m2.port++;
        m2.port++ <--> C <--> m3.port++;
        m2.port++ <--> C <--> m4.port++;
        m4.port++ <--> C <--> n1.port++;
        m3.port++ <--> C <--> n1.port++;
        n1.port++ <--> C <--> n2.port++;
        n2.port++ <--> C <--> n4.port++;
        n4.port++ <--> C <--> m1.port++;
}

