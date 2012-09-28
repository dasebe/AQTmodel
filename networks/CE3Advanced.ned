package adversarialqueueing.networks;

import adversarialqueueing.adversaries.CE3Advanced;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;


//
// This is the basic omnet network description of a circular (complete) form of CE3.
//
network CE3Advanced
{
    @display("bgb=688,735,white,,0");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        adversary: CE3Advanced {
            @display("p=346,280;b=25,25,rect,grey83");
        }

        n12: SourceRoutingNode {
            @display("p=155,127;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 112;
        }
        n22: SourceRoutingNode {
            @display("p=268,169;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 122;
        }
        n11: SourceRoutingNode {
            @display("p=562,127;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 111;
        }
        n91: SourceRoutingNode {
            @display("p=212,253;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 191;
        }
        n92: SourceRoutingNode {
            @display("p=212,338;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 192;
        }
        m11: SourceRoutingNode {
            @display("p=155,470;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 211;
        }
        m21: SourceRoutingNode {
            @display("p=268,425;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 221;
        }
        n21: SourceRoutingNode {
            @display("p=423,169;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 121;
        }
        m22: SourceRoutingNode {
            @display("p=423,425;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 222;
        }
        m12: SourceRoutingNode {
            @display("p=562,470;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 212;
        }
        m92: SourceRoutingNode {
            @display("p=491,253;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 292;
        }
        m91: SourceRoutingNode {
            @display("p=491,338;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 291;
        }
    connections:

        n22.port++ <--> C <--> n91.port++;
        n91.port++ <--> C <--> n92.port++;
        n12.port++ <--> C <--> n91.port++;
        n11.port++ <--> C <--> n12.port++;
        n21.port++ <--> C <--> n22.port++;
        m21.port++ <--> C <--> m22.port++;
        m11.port++ <--> C <--> m12.port++;
        m12.port++ <--> C <--> m91.port++;
        m22.port++ <--> C <--> m91.port++;
        m91.port++ <--> C <--> m92.port++;
        m92.port++ <--> C <--> n21.port++;
        m22.port++ <--> C <--> n21.port++;
        m92.port++ <--> C <--> n11.port++;
        m12.port++ <--> C <--> n11.port++;
        n22.port++ <--> C <--> m21.port++;
        n92.port++ <--> C <--> m21.port++;
        n12.port++ <--> C <--> m11.port++;
        n92.port++ <--> C <--> m11.port++;
}

