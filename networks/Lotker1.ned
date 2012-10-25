
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.AdvancedAdversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;


//
// This is the basic omnet network description of a circular model for CE7. 
//
network Lotker1
{
    parameters:
        string adType;
        @display("bgb=920,735,white,,0");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        adversary: <adType> like AdvancedAdversary {
            @display("p=12,17;b=25,25,rect,grey83");
        }

        a01: SourceRoutingNode {
            @display("p=29,132;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 101;
        }
        a02: SourceRoutingNode {
            @display("p=65,204;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 102;
        }
        a11: SourceRoutingNode {
            @display("p=101,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 111;
        }
        a21: SourceRoutingNode {
            @display("p=101,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 121;
        }
        a12: SourceRoutingNode {
            @display("p=147,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 112;
        }
        a22: SourceRoutingNode {
            @display("p=147,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 122;
        }
        a13: SourceRoutingNode {
            @display("p=186,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 113;
        }
        a23: SourceRoutingNode {
            @display("p=186,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 123;
        }
        a14: SourceRoutingNode {
            @display("p=229,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 114;
        }
        a24: SourceRoutingNode {
            @display("p=229,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 124;
        }
        a15: SourceRoutingNode {
            @display("p=274,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 115;
        }
        a25: SourceRoutingNode {
            @display("p=274,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 125;
        }
        a16: SourceRoutingNode {
            @display("p=314,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 116;
        }
        a26: SourceRoutingNode {
            @display("p=314,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 126;
        }
        a17: SourceRoutingNode {
            @display("p=363,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 117;
        }
        a27: SourceRoutingNode {
            @display("p=363,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 127;
        }
        a18: SourceRoutingNode {
            @display("p=404,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 118;
        }
        a28: SourceRoutingNode {
            @display("p=404,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 128;
        }


        b01: SourceRoutingNode {
            @display("p=440,204;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 201;
        }
        b02: SourceRoutingNode {
            @display("p=482,204;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 202;
        }
        b11: SourceRoutingNode {
            @display("p=518,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 211;
        }
        b21: SourceRoutingNode {
            @display("p=518,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 221;
        }
        b12: SourceRoutingNode {
            @display("p=564,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 212;
        }
        b22: SourceRoutingNode {
            @display("p=564,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 222;
        }
        b13: SourceRoutingNode {
            @display("p=603,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 213;
        }
        b23: SourceRoutingNode {
            @display("p=603,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 223;
        }
        b14: SourceRoutingNode {
            @display("p=646,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 214;
        }
        b24: SourceRoutingNode {
            @display("p=646,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 224;
        }
        b15: SourceRoutingNode {
            @display("p=691,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 215;
        }
        b25: SourceRoutingNode {
            @display("p=691,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 225;
        }
        b16: SourceRoutingNode {
            @display("p=731,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 216;
        }
        b26: SourceRoutingNode {
            @display("p=731,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 226;
        }
        b17: SourceRoutingNode {
            @display("p=780,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 217;
        }
        b27: SourceRoutingNode {
            @display("p=780,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 227;
        }
        b18: SourceRoutingNode {
            @display("p=821,163;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 218;
        }
        b28: SourceRoutingNode {
            @display("p=821,249;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 228;
        }

        c01: SourceRoutingNode {
            @display("p=868,204;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 301;
        }
        c02: SourceRoutingNode {
            @display("p=909,132;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 302;
        }
    connections:


        a01.port++ <--> C  <--> a02.port++;
        a02.port++ <--> C  <--> a11.port++;
        a02.port++ <--> C  <--> a21.port++;
        a11.port++ <--> C  <--> a12.port++;
        a21.port++ <--> C  <--> a22.port++;
        a12.port++ <--> C  <--> a13.port++;
        a22.port++ <--> C  <--> a23.port++;
        a13.port++ <--> C  <--> a14.port++;
        a23.port++ <--> C  <--> a24.port++;
        a14.port++ <--> C  <--> a15.port++;
        a24.port++ <--> C  <--> a25.port++;
        a15.port++ <--> C  <--> a16.port++;
        a25.port++ <--> C  <--> a26.port++;
        a16.port++ <--> C  <--> a17.port++;
        a26.port++ <--> C  <--> a27.port++;
        a17.port++ <--> C  <--> a18.port++;
        a27.port++ <--> C  <--> a28.port++;
        a18.port++ <--> C  <--> b01.port++;
        a28.port++ <--> C  <--> b01.port++;
        b01.port++ <--> C  <--> b02.port++;
        b02.port++ <--> C  <--> b11.port++;
        b02.port++ <--> C  <--> b21.port++;
        b11.port++ <--> C  <--> b12.port++;
        b21.port++ <--> C  <--> b22.port++;
        b12.port++ <--> C  <--> b13.port++;
        b22.port++ <--> C  <--> b23.port++;
        b13.port++ <--> C  <--> b14.port++;
        b23.port++ <--> C  <--> b24.port++;
        b14.port++ <--> C  <--> b15.port++;
        b24.port++ <--> C  <--> b25.port++;
        b15.port++ <--> C  <--> b16.port++;
        b25.port++ <--> C  <--> b26.port++;
        b16.port++ <--> C  <--> b17.port++;
        b26.port++ <--> C  <--> b27.port++;
        b17.port++ <--> C  <--> b18.port++;
        b27.port++ <--> C  <--> b28.port++;
        b18.port++ <--> C  <--> c01.port++;
        b28.port++ <--> C  <--> c01.port++;
        c01.port++ <--> C  <--> c02.port++;
        c02.port++ <--> C  <--> a01.port++;
}

