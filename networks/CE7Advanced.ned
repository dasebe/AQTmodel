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
            @display("p=93,45;b=25,25,rect,grey83");
        }

        n12: SourceRoutingNode {
            @display("p=25,214;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 112;
        }
        n91: SourceRoutingNode {
            @display("p=94,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 191;
        }
        n22: SourceRoutingNode {
            @display("p=156,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 122;
        }
        n92: SourceRoutingNode {
            @display("p=94,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 192;
        }
        n11: SourceRoutingNode {
            @display("p=365,74;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 111;
        }
        n32: SourceRoutingNode {
            @display("p=275,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 132;
        }
        n94: SourceRoutingNode {
            @display("p=215,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 194;
        }
        n95: SourceRoutingNode {
            @display("p=215,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 195;
        }
        n93: SourceRoutingNode {
            @display("p=94,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 193;
        }
        n13: SourceRoutingNode {
            @display("p=25,536;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 113;
        }
        m11: SourceRoutingNode {
            @display("p=365,703;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 211;
        }
        n23: SourceRoutingNode {
            @display("p=156,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 123;
        }
        m21: SourceRoutingNode {
            @display("p=365,666;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 221;
        }
        n33: SourceRoutingNode {
            @display("p=275,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 133;
        }
        m31: SourceRoutingNode {
            @display("p=365,629;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 231;
        }
        n21: SourceRoutingNode {
            @display("p=365,103;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 121;
        }
        n31: SourceRoutingNode {
            @display("p=365,139;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 131;
        }
        m32: SourceRoutingNode {
            @display("p=448,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 232;
        }
        m22: SourceRoutingNode {
            @display("p=558,546;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 222;
        }
        m12: SourceRoutingNode {
            @display("p=661,536;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 212;
        }
        m91: SourceRoutingNode {
            @display("p=611,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 291;
        }
        m92: SourceRoutingNode {
            @display("p=611,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 292;
        }
        m93: SourceRoutingNode {
            @display("p=611,314;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 293;
        }
        m95: SourceRoutingNode {
            @display("p=502,383;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 295;
        }
        m94: SourceRoutingNode {
            @display("p=502,458;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 294;
        }
        m33: SourceRoutingNode {
            @display("p=448,226;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 233;
        }
        m23: SourceRoutingNode {
            @display("p=558,224;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 223;
        }
        m13: SourceRoutingNode {
            @display("p=661,214;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 213;
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
        n93.port++ <--> C <--> n13.port++;
        n13.port++ <--> C <--> m11.port++;
        n93.port++ <--> C <--> n23.port++;
        n23.port++ <--> C <--> m21.port++;
        n93.port++ <--> C <--> n33.port++;
        n95.port++ <--> C <--> n13.port++;
        n95.port++ <--> C <--> n23.port++;
        n95.port++ <--> C <--> n33.port++;
        n33.port++ <--> C <--> m31.port++;
        n12.port++ <--> C <--> n94.port++;
        n32.port++ <--> C <--> n91.port++;
        n12.port++ <--> C <--> n13.port++;
        n22.port++ <--> C <--> n23.port++;
        n32.port++ <--> C <--> n33.port++;
        n11.port++ <--> C <--> n12.port++;
        n21.port++ <--> C <--> n22.port++;
        n31.port++ <--> C <--> n32.port++;
        m31.port++ <--> C <--> m32.port++;
        m21.port++ <--> C <--> m22.port++;
        m11.port++ <--> C <--> m12.port++;
        m12.port++ <--> C <--> m91.port++;
        m12.port++ <--> C <--> m94.port++;
        m12.port++ <--> C <--> m13.port++;
        m22.port++ <--> C <--> m91.port++;
        m22.port++ <--> C <--> m94.port++;
        m22.port++ <--> C <--> m23.port++;
        m32.port++ <--> C <--> m91.port++;
        m32.port++ <--> C <--> m94.port++;
        m32.port++ <--> C <--> m33.port++;
        m91.port++ <--> C <--> m92.port++;
        m92.port++ <--> C <--> m93.port++;
        m94.port++ <--> C <--> m95.port++;
        m95.port++ <--> C <--> m33.port++;
        m95.port++ <--> C <--> m23.port++;
        m95.port++ <--> C <--> m13.port++;
        m93.port++ <--> C <--> m33.port++;
        m93.port++ <--> C <--> m23.port++;
        m93.port++ <--> C <--> m13.port++;
        m33.port++ <--> C <--> n31.port++;
        m23.port++ <--> C <--> n21.port++;
        m13.port++ <--> C <--> n11.port++;
        m95.port++ <--> C <--> m92.port++;
}

