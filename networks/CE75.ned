
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;


//
// This is the basic omnet network description of a circular model for CE7. 
//
network CE75
{
    parameters:
        string adType;
        @display("bgb=688,735,white,,0");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        adversary: <adType> like AdvancedAdversary {
            @display("p=345,331;b=25,25,rect,grey83");
        }

        n12: SourceRoutingNode {
            @display("p=27,74;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 112;
        }
        n91: SourceRoutingNode {
            @display("p=81,263;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 191;
        }
        n22: SourceRoutingNode {
            @display("p=111,123;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 122;
        }
        n92: SourceRoutingNode {
            @display("p=81,332;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 192;
        }
        n11: SourceRoutingNode {
            @display("p=648,74;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 111;
        }
        n32: SourceRoutingNode {
            @display("p=164,162;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 132;
        }
        n94: SourceRoutingNode {
            @display("p=202,263;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 194;
        }
        n95: SourceRoutingNode {
            @display("p=202,332;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 195;
        }
        n93: SourceRoutingNode {
            @display("p=81,407;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 193;
        }
        m11: SourceRoutingNode {
            @display("p=27,595;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 211;
        }
        m21: SourceRoutingNode {
            @display("p=111,553;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 221;
        }
        m31: SourceRoutingNode {
            @display("p=164,508;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 231;
        }
        n21: SourceRoutingNode {
            @display("p=568,123;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 121;
        }
        n31: SourceRoutingNode {
            @display("p=516,162;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 131;
        }
        m32: SourceRoutingNode {
            @display("p=516,508;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 232;
        }
        m22: SourceRoutingNode {
            @display("p=568,553;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 222;
        }
        m12: SourceRoutingNode {
            @display("p=648,595;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 212;
        }
        m91: SourceRoutingNode {
            @display("p=598,407;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 291;
        }
        m92: SourceRoutingNode {
            @display("p=598,332;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 292;
        }
        m93: SourceRoutingNode {
            @display("p=598,263;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 293;
        }
        m95: SourceRoutingNode {
            @display("p=489,332;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 295;
        }
        m94: SourceRoutingNode {
            @display("p=489,407;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 294;
        }
        n42: SourceRoutingNode {
            @display("p=256,211;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 142;
        }
        n41: SourceRoutingNode {
            @display("p=450,211;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 141;
        }
        n52: SourceRoutingNode {
            @display("p=295,263;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 152;
        }
        n51: SourceRoutingNode {
            @display("p=396,263;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 151;
        }
        m42: SourceRoutingNode {
            @display("p=450,461;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 242;
        }
        m41: SourceRoutingNode {
            @display("p=256,461;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 241;
        }
        m51: SourceRoutingNode {
            @display("p=295,407;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 251;
        }
        m52: SourceRoutingNode {
            @display("p=396,407;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 252;
        }
    connections:

        n91.port++ <--> C <--> n22.port++;
        n12.port++ <--> C <--> n91.port++;
        n91.port++ <--> C <--> n92.port++;
        n32.port++ <--> C <--> n94.port++;
        n22.port++ <--> C <--> n94.port++;
        n94.port++ <--> C <--> n95.port++;
        n95.port++ <--> C <--> n92.port++;
        n92.port++ <--> C <--> n93.port++;
        n12.port++ <--> C <--> n94.port++;
        n32.port++ <--> C <--> n91.port++;
        n11.port++ <--> C <--> n12.port++;
        n21.port++ <--> C <--> n22.port++;
        n31.port++ <--> C <--> n32.port++;
        m31.port++ <--> C <--> m32.port++;
        m21.port++ <--> C <--> m22.port++;
        m11.port++ <--> C <--> m12.port++;
        m12.port++ <--> C <--> m91.port++;
        m12.port++ <--> C <--> m94.port++;
        m22.port++ <--> C <--> m91.port++;
        m22.port++ <--> C <--> m94.port++;
        m32.port++ <--> C <--> m91.port++;
        m32.port++ <--> C <--> m94.port++;
        m91.port++ <--> C <--> m92.port++;
        m92.port++ <--> C <--> m93.port++;
        m94.port++ <--> C <--> m95.port++;
        m95.port++ <--> C <--> m92.port++;
        m32.port++ <--> C <--> n31.port++;
        m95.port++ <--> C <--> n31.port++;
        m93.port++ <--> C <--> n31.port++;
        m95.port++ <--> C <--> n21.port++;
        m22.port++ <--> C <--> n21.port++;
        m93.port++ <--> C <--> n21.port++;
        m95.port++ <--> C <--> n11.port++;
        m93.port++ <--> C <--> n11.port++;
        m12.port++ <--> C <--> n11.port++;
        n32.port++ <--> C <--> m31.port++;
        n95.port++ <--> C <--> m31.port++;
        n93.port++ <--> C <--> m31.port++;
        n22.port++ <--> C <--> m21.port++;
        n95.port++ <--> C <--> m21.port++;
        n93.port++ <--> C <--> m21.port++;
        n12.port++ <--> C <--> m11.port++;
        n93.port++ <--> C <--> m11.port++;
        n95.port++ <--> C <--> m11.port++;
        m42.port++ <--> C <--> n41.port++;
        n41.port++ <--> C <--> n42.port++;
        n42.port++ <--> C <--> m41.port++;
        m41.port++ <--> C <--> m42.port++;
        m42.port++ <--> C <--> m91.port++;
        m42.port++ <--> C <--> m94.port++;
        m95.port++ <--> C <--> n41.port++;
        m93.port++ <--> C <--> n41.port++;
        n42.port++ <--> C <--> n94.port++;
        n42.port++ <--> C <--> n91.port++;
        n93.port++ <--> C <--> m41.port++;
        n95.port++ <--> C <--> m41.port++;
        m51.port++ <--> C <--> m52.port++;
        m52.port++ <--> C <--> n51.port++;
        n51.port++ <--> C <--> n52.port++;
        n52.port++ <--> C <--> m51.port++;
        n52.port++ <--> C <--> n94.port++;
        n52.port++ <--> C <--> n91.port++;
        n93.port++ <--> C <--> m51.port++;
        n95.port++ <--> C <--> m51.port++;
        m52.port++ <--> C <--> m94.port++;
        m52.port++ <--> C <--> m91.port++;
        m95.port++ <--> C <--> n51.port++;
        m92.port++ <--> C <--> n51.port++;
}

