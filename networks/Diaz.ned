
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.adversaries.Randomization;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network Diaz
{
    parameters:
        string adType;
        @display("bgb=409,414,white");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:
        adversary: <adType> like AdvancedAdversary {
            @display("p=319,77;i=block/blackboard,#AA0000;is=s");
        }
        n1: SourceRoutingNode {
            @display("p=253,11;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 11;
        }
        n2: SourceRoutingNode {
            @display("p=65,11;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 12;
        }
        n3: SourceRoutingNode {
            @display("p=18,184;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 13;
        }
        n4: SourceRoutingNode {
            @display("p=122,126;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 14;
        }
		n5: SourceRoutingNode {
            @display("p=65,126;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 15;
        }
        n6: SourceRoutingNode {
            @display("p=91,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 16;
        }
        m1: SourceRoutingNode {
            @display("p=65,334;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 21;
        }
        m2: SourceRoutingNode {
            @display("p=253,334;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 22;
        }
        m4: SourceRoutingNode {
            @display("p=183,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 24;
        }
        m3: SourceRoutingNode {
            @display("p=300,184;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 23;
        }
        m5: SourceRoutingNode {
            @display("p=253,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 25;
        }
        m6: SourceRoutingNode {
            @display("p=213,126;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 26;
        }
		randomization: Randomization {
            @display("p=312,28;i=status/ctrl");
        }
    connections:

        n2.port++ <--> C <--> n3.port++;
        n3.port++ <--> C <--> m1.port++;
        m1.port++ <--> C <--> m2.port++;
        m2.port++ <--> C <--> m3.port++;
        m3.port++ <--> C <--> n1.port++;
        n1.port++ <--> C <--> n2.port++;
        n2.port++ <--> C <-->  n5.port++;
        n2.port++ <--> C <-->  n4.port++;
        n5.port++ <--> C <-->  n6.port++;
        n4.port++ <--> C <-->  n6.port++;
        n6.port++ <--> C <-->  m1.port++;
        m2.port++ <--> C <-->  m4.port++;
        m2.port++ <--> C <-->  m5.port++;
        m4.port++ <--> C <-->  m6.port++;
        m5.port++ <--> C <-->  m6.port++;
        m6.port++ <--> C <-->  n1.port++;
}

