
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import adversarialqueueing.channelvariation.VDrChannel;

//
// This is the basic omnet network description of a simple Baseball network. 
//
network VarAPlusMinor
{
    parameters:
        string adType;
        @display("bgb=267,165,white");
    types:
        channel C extends VDrChannel
        {
        }
    submodules:
        adversary: <adType> like AdvancedAdversary {
            @display("p=232,17;i=block/blackboard,#AA0000;is=s");
        }
        A: SourceRoutingNode {
            @display("p=19,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1;
        }
        D: SourceRoutingNode {
            @display("p=154,36;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 21;
        }
        E: SourceRoutingNode {
            @display("p=154,100;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 22;
        }
        B: SourceRoutingNode {
            @display("p=245,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 3;
        }
        F: SourceRoutingNode {
            @display("p=213,142;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 4;
        }
        C: SourceRoutingNode {
            @display("p=50,142;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 5;
        }
    connections:

        A.port++ <--> C <--> D.port++;
        D.port++ <--> C <--> B.port++;
        A.port++ <--> C <--> E.port++;
        E.port++ <--> C <--> B.port++;
        B.port++ <--> C <--> F.port++;
        F.port++ <--> C <--> C.port++;
        C.port++ <--> C <--> A.port++;
}

