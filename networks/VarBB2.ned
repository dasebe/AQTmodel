
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import adversarialqueueing.networks.VChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network VarBB2
{
    parameters:
        string adType;
        @display("bgb=358,408,white");
    types:
        channel C extends ThruputMeteringChannel
        {
            datarate=10Mbps;
            meanDatarate=10Mbps;
            stdDatarate=3Mbps;
        }
    submodules:
        adversary: <adType> like AdvancedAdversary {
            @display("p=135,77;i=block/blackboard,#AA0000;is=s");
        }
        n1: SourceRoutingNode {
            @display("p=240,40;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 11;
        }
        n2: SourceRoutingNode {
            @display("p=66,40;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 12;
        }
        n3: SourceRoutingNode {
            @display("p=29,213;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 13;
        }
        n4: SourceRoutingNode {
            @display("p=108,213;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 14;
        }
        m1: SourceRoutingNode {
            @display("p=66,363;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 21;
        }
        m2: SourceRoutingNode {
            @display("p=240,363;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 22;
        }
        m4: SourceRoutingNode {
            @display("p=177,213;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 24;
        }
        m3: SourceRoutingNode {
            @display("p=285,213;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
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

