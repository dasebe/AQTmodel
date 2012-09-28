//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package networks;

import adversaries.CE7Advanced;
import node.SourceRouting;
import node.SourceRoutingNode;
import ned.DatarateChannel;

//
// A ten-node network topology
//
network CE7Advanced
{
    @display("bgb=688,735,white,,0");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        adversary: CE7Advanced {
            @display("p=38,38;b=25,25,rect,grey83");
        }

        a2: SourceRoutingNode {
            @display("p=25,214;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 12;
        }
        m1: SourceRoutingNode {
            @display("p=94,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 91;
        }
        b2: SourceRoutingNode {
            @display("p=156,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 22;
        }
        m2: SourceRoutingNode {
            @display("p=94,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 92;
        }
        a1: SourceRoutingNode {
            @display("p=340,26;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 11;
        }
        c2: SourceRoutingNode {
            @display("p=275,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 32;
        }
        m4: SourceRoutingNode {
            @display("p=215,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 94;
        }
        m5: SourceRoutingNode {
            @display("p=215,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 95;
        }
        m3: SourceRoutingNode {
            @display("p=94,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 93;
        }
        a3: SourceRoutingNode {
            @display("p=25,536;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 13;
        }
        a4: SourceRoutingNode {
            @display("p=340,709;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 14;
        }
        b3: SourceRoutingNode {
            @display("p=156,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 23;
        }
        b4: SourceRoutingNode {
            @display("p=340,661;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 24;
        }
        c3: SourceRoutingNode {
            @display("p=275,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 33;
        }
        c4: SourceRoutingNode {
            @display("p=340,611;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 34;
        }
        b1: SourceRoutingNode {
            @display("p=340,67;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 21;
        }
        c1: SourceRoutingNode {
            @display("p=340,109;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 31;
        }
        c5: SourceRoutingNode {
            @display("p=448,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 35;
        }
        b5: SourceRoutingNode {
            @display("p=558,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 25;
        }
        a5: SourceRoutingNode {
            @display("p=661,536;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 15;
        }
        m6: SourceRoutingNode {
            @display("p=611,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 96;
        }
        m7: SourceRoutingNode {
            @display("p=611,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 97;
        }
        m8: SourceRoutingNode {
            @display("p=611,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 98;
        }
        m10: SourceRoutingNode {
            @display("p=502,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 910;
        }
        m9: SourceRoutingNode {
            @display("p=502,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 99;
        }
        c6: SourceRoutingNode {
            @display("p=448,226;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 36;
        }
        b6: SourceRoutingNode {
            @display("p=558,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 26;
        }
        a6: SourceRoutingNode {
            @display("p=661,214;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 16;
        }
    connections:

        m1.port++ <--> C <--> b2.port++;
        a2.port++ <--> C <--> m1.port++;
        m1.port++ <--> C <--> m2.port++;
        c2.port++ <--> C <--> m4.port++;
        b2.port++ <--> C <--> m4.port++;
        m4.port++ <--> C <--> m5.port++;
        m5.port++ <--> C <--> m2.port++;
        m2.port++ <--> C <--> m3.port++;
        m3.port++ <--> C <--> a3.port++;
        a3.port++ <--> C <--> a4.port++;
        m3.port++ <--> C <--> b3.port++;
        b3.port++ <--> C <--> b4.port++;
        m3.port++ <--> C <--> c3.port++;
        m5.port++ <--> C <--> a3.port++;
        m5.port++ <--> C <--> b3.port++;
        m5.port++ <--> C <--> c3.port++;
        c3.port++ <--> C <--> c4.port++;
        a2.port++ <--> C <--> m4.port++;
        c2.port++ <--> C <--> m1.port++;
        a2.port++ <--> C <--> a3.port++;
        b2.port++ <--> C <--> b3.port++;
        c2.port++ <--> C <--> c3.port++;
        a1.port++ <--> C <--> a2.port++;
        b1.port++ <--> C <--> b2.port++;
        c1.port++ <--> C <--> c2.port++;
        c4.port++ <--> C <--> c5.port++;
        b4.port++ <--> C <--> b5.port++;
        a4.port++ <--> C <--> a5.port++;
        a5.port++ <--> C <--> m6.port++;
        a5.port++ <--> C <--> m9.port++;
        a5.port++ <--> C <--> a6.port++;
        b5.port++ <--> C <--> m6.port++;
        b5.port++ <--> C <--> m9.port++;
        b5.port++ <--> C <--> b6.port++;
        c5.port++ <--> C <--> m6.port++;
        c5.port++ <--> C <--> m9.port++;
        c5.port++ <--> C <--> c6.port++;
        m6.port++ <--> C <--> m7.port++;
        m7.port++ <--> C <--> m8.port++;
        m9.port++ <--> C <--> m10.port++;
        m10.port++ <--> C <--> c6.port++;
        m10.port++ <--> C <--> b6.port++;
        m10.port++ <--> C <--> a6.port++;
        m8.port++ <--> C <--> c6.port++;
        m8.port++ <--> C <--> b6.port++;
        m8.port++ <--> C <--> a6.port++;
        c6.port++ <--> C <--> c1.port++;
        b6.port++ <--> C <--> b1.port++;
        a6.port++ <--> C <--> a1.port++;
        m10.port++ <--> m7.port++;
}

