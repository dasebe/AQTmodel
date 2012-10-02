
package adversarialqueueing.networks;

import adversarialqueueing.adversaries.CE7Adversary;
import adversarialqueueing.node.SourceRouting;
import adversarialqueueing.node.SourceRoutingNode;
import ned.DatarateChannel;


//
// This is the basic omnet network description of CE7. 
//
//
network CE7half
{
    @display("bgb=564,692");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        a2: SourceRoutingNode {
            @display("p=214,192");
            address = 12;
        }
        m1: SourceRoutingNode {
            @display("p=281,282");
            address = 91;
        }
        b2: SourceRoutingNode {
            @display("p=343,192");
            address = 22;
        }
        adversary: CE7Adversary {
            @display("p=55,219");
        }
        a1: SourceRoutingNode {
            @display("p=214,118");
            address = 11;
        }
        b1: SourceRoutingNode {
            @display("p=343,118");
            address = 21;
        }
        m2: SourceRoutingNode {
            @display("p=281,351");
            address = 92;
        }
        a0: SourceRoutingNode {
            @display("p=214,18");
            address = 10;
        }
        a01: SourceRoutingNode {
            @display("p=214,57");
            address = 101;
        }
        a02: SourceRoutingNode {
            @display("p=185,85");
            address = 102;
        }
        a03: SourceRoutingNode {
            @display("p=244,85");
            address = 103;
        }
        c1: SourceRoutingNode {
            @display("p=462,118");
            address = 31;
        }
        c2: SourceRoutingNode {
            @display("p=462,192");
            address = 32;
        }
        m4: SourceRoutingNode {
            @display("p=402,282");
            address = 94;
        }
        m5: SourceRoutingNode {
            @display("p=402,351");
            address = 95;
        }
        m3: SourceRoutingNode {
            @display("p=281,426");
            address = 93;
        }
        a3: SourceRoutingNode {
            @display("p=214,514");
            address = 13;
        }
        a4: SourceRoutingNode {
            @display("p=214,589");
            address = 14;
        }
        b3: SourceRoutingNode {
            @display("p=343,514");
            address = 23;
        }
        b4: SourceRoutingNode {
            @display("p=343,589");
            address = 24;
        }
        c3: SourceRoutingNode {
            @display("p=462,514");
            address = 33;
        }
        c4: SourceRoutingNode {
            @display("p=462,589");
            address = 34;
        }
        b0: SourceRoutingNode {
            @display("p=343,18");
            address = 20;
        }
        c0: SourceRoutingNode {
            @display("p=462,18");
            address = 30;
        }
    connections:

        m1.port++ <--> C <--> b2.port++;
        a2.port++ <--> C <--> a1.port++;
        b1.port++ <--> C <--> b2.port++;
        a2.port++ <--> C <--> m1.port++;
        m1.port++ <--> C <--> m2.port++;
        a0.port++ <--> C <--> a01.port++;
        a01.port++ <--> C <--> a02.port++;
        a02.port++ <--> C <--> a1.port++;
        a01.port++ <--> C <--> a03.port++;
        a03.port++ <--> C <--> a1.port++;
        b0.port++ <--> C <--> b1.port++;
        c0.port++ <--> C <--> c1.port++;
        c1.port++ <--> C <--> c2.port++;
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
}

