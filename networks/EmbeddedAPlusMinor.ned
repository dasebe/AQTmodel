
package adversarialqueueing.networks;

import adversarialqueueing.TraditionalSourceSink.Sink;
import adversarialqueueing.TraditionalSourceSink.Source;
import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.adversaries.Randomization;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network EmbeddedAPlusMinor
{
    parameters:
        string adType;
        @display("bgb=469,332,white");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:
        adversary: <adType> like AdvancedAdversary {
            @display("p=141,14;i=block/blackboard,#AA0000;is=s");
        }
        A: SourceRoutingNode {
            @display("p=96,143;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1;
        }
        D: SourceRoutingNode {
            @display("p=231,109;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 21;
        }
        E: SourceRoutingNode {
            @display("p=231,173;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 22;
        }
        B: SourceRoutingNode {
            @display("p=322,143;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 2;
        }
        F: SourceRoutingNode {
            @display("p=290,215;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 3;
        }
        C: SourceRoutingNode {
            @display("p=127,215;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 4;
        }
        N1: SourceRoutingNode {
            @display("p=96,79;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 5;
        }
        N2: SourceRoutingNode {
            @display("p=231,50;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 6;
        }
        N3: SourceRoutingNode {
            @display("p=216,266;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 7;
        }
        N4: SourceRoutingNode {
            @display("p=400,124;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 8;
        }
        N5: SourceRoutingNode {
            @display("p=356,266;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 9;
        }
        N6: SourceRoutingNode {
            @display("p=65,266;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 10;
        }
        randomization: Randomization {
            @display("p=53,18;i=status/ctrl");
        }
        s1: Source {
            @display("p=29,79;is=s");
        }
        s4: Source {
            @display("p=310,56;is=s");
        }
        s2: Source {
            @display("p=22,276;is=s");
        }
        s3: Source {
            @display("p=188,21;is=s");
        }
        s5: Source {
            @display("p=398,294;is=s");
        }
    connections:

        A.port++ <--> C <--> D.port++;
        D.port++ <--> C <--> B.port++;
        A.port++ <--> C <--> E.port++;
        E.port++ <--> C <--> B.port++;
        B.port++ <--> C <--> F.port++;
        F.port++ <--> C <--> C.port++;
        C.port++ <--> C <--> A.port++;
        s1.out <--> C <--> N1.port++;
        N1.port++ <--> C <--> A.port++;
        C.port++ <--> C <--> N6.port++;
        C.port++ <--> C <--> N3.port++;
        D.port++ <--> C <--> N2.port++;
        B.port++ <--> C <--> N4.port++;
        B.port++ <--> C <--> N5.port++;
        s2.out <--> C <--> N6.port++;
        s3.out <--> C <--> N2.port++;
        s4.out <--> C <--> N4.port++;
        s5.out <--> C <--> N5.port++;
}

