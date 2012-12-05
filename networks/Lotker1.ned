
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
        @display("bgb=2006,383,white,,0");
    types:
        channel C extends DatarateChannel
        {
            delay = 0ms;
            datarate = 10Mbps;
        }
    submodules:

        adversary: <adType> like AdvancedAdversary {
            @display("p=986,10;i=block/blackboard,#AA0000;is=s");
        }

        a00: SourceRoutingNode {
            @display("p=13,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 100;
        }

        a01: SourceRoutingNode {
            @display("p=13,196;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 101;
        }
        a02: SourceRoutingNode {
            @display("p=13,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 102;
        }
        a11: SourceRoutingNode {
            @display("p=49,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 111;
        }
        a21: SourceRoutingNode {
            @display("p=49,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 121;
        }
        a12: SourceRoutingNode {
            @display("p=87,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 112;
        }
        a22: SourceRoutingNode {
            @display("p=87,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 122;
        }
        a13: SourceRoutingNode {
            @display("p=126,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 113;
        }
        a23: SourceRoutingNode {
            @display("p=126,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 123;
        }
        a14: SourceRoutingNode {
            @display("p=164,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 114;
        }
        a24: SourceRoutingNode {
            @display("p=164,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 124;
        }
        a15: SourceRoutingNode {
            @display("p=203,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 115;
        }
        a25: SourceRoutingNode {
            @display("p=203,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 125;
        }
        a16: SourceRoutingNode {
            @display("p=238,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 116;
        }
        a26: SourceRoutingNode {
            @display("p=238,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 126;
        }
        a17: SourceRoutingNode {
            @display("p=275,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 117;
        }
        a27: SourceRoutingNode {
            @display("p=275,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 127;
        }
        a18: SourceRoutingNode {
            @display("p=309,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 118;
        }
        a28: SourceRoutingNode {
            @display("p=309,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 128;
        }
        a19: SourceRoutingNode {
            @display("p=344,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 119;
        }
        a29: SourceRoutingNode {
            @display("p=344,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 129;
        }




        b01: SourceRoutingNode {
            @display("p=372,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 201;
        }
        b02: SourceRoutingNode {
            @display("p=405,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 202;
        }
        b11: SourceRoutingNode {
            @display("p=441,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 211;
        }
        b21: SourceRoutingNode {
            @display("p=441,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 221;
        }
        b12: SourceRoutingNode {
            @display("p=479,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 212;
        }
        b22: SourceRoutingNode {
            @display("p=479,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 222;
        }
        b13: SourceRoutingNode {
            @display("p=518,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 213;
        }
        b23: SourceRoutingNode {
            @display("p=518,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 223;
        }
        b14: SourceRoutingNode {
            @display("p=556,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 214;
        }
        b24: SourceRoutingNode {
            @display("p=556,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 224;
        }
        b15: SourceRoutingNode {
            @display("p=595,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 215;
        }
        b25: SourceRoutingNode {
            @display("p=595,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 225;
        }
        b16: SourceRoutingNode {
            @display("p=630,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 216;
        }
        b26: SourceRoutingNode {
            @display("p=630,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 226;
        }
        b17: SourceRoutingNode {
            @display("p=667,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 217;
        }
        b27: SourceRoutingNode {
            @display("p=667,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 227;
        }
        b18: SourceRoutingNode {
            @display("p=701,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 218;
        }
        b28: SourceRoutingNode {
            @display("p=701,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 228;
        }
        b19: SourceRoutingNode {
            @display("p=736,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 219;
        }
        b29: SourceRoutingNode {
            @display("p=736,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 229;
        }



        c01: SourceRoutingNode {
            @display("p=775,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 301;
        }
        c02: SourceRoutingNode {
            @display("p=810,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 302;
        }
        c11: SourceRoutingNode {
            @display("p=853,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 311;
        }
        c21: SourceRoutingNode {
            @display("p=853,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 321;
        }
        c12: SourceRoutingNode {
            @display("p=891,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 312;
        }
        c22: SourceRoutingNode {
            @display("p=891,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 322;
        }
        c13: SourceRoutingNode {
            @display("p=930,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 313;
        }
        c23: SourceRoutingNode {
            @display("p=930,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 323;
        }
        c14: SourceRoutingNode {
            @display("p=968,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 314;
        }
        c24: SourceRoutingNode {
            @display("p=968,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 324;
        }
        c15: SourceRoutingNode {
            @display("p=1007,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 315;
        }
        c25: SourceRoutingNode {
            @display("p=1007,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 325;
        }
        c16: SourceRoutingNode {
            @display("p=1042,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 316;
        }
        c26: SourceRoutingNode {
            @display("p=1042,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 326;
        }
        c17: SourceRoutingNode {
            @display("p=1079,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 317;
        }
        c27: SourceRoutingNode {
            @display("p=1079,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 327;
        }
        c18: SourceRoutingNode {
            @display("p=1113,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 318;
        }
        c28: SourceRoutingNode {
            @display("p=1113,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 328;
        }
        c19: SourceRoutingNode {
            @display("p=1148,70;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 319;
        }
        c29: SourceRoutingNode {
            @display("p=1148,156;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 329;
        }



        d01: SourceRoutingNode {
            @display("p=1184,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 401;
        }
        d02: SourceRoutingNode {
            @display("p=1216,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 402;
        }
        d11: SourceRoutingNode {
            @display("p=1252,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 411;
        }
        d21: SourceRoutingNode {
            @display("p=1252,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 421;
        }
        d12: SourceRoutingNode {
            @display("p=1290,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 412;
        }
        d22: SourceRoutingNode {
            @display("p=1290,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 422;
        }
        d13: SourceRoutingNode {
            @display("p=1329,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 413;
        }
        d23: SourceRoutingNode {
            @display("p=1329,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 423;
        }
        d14: SourceRoutingNode {
            @display("p=1367,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 414;
        }
        d24: SourceRoutingNode {
            @display("p=1367,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 424;
        }
        d15: SourceRoutingNode {
            @display("p=1406,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 415;
        }
        d25: SourceRoutingNode {
            @display("p=1406,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 425;
        }
        d16: SourceRoutingNode {
            @display("p=1441,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 416;
        }
        d26: SourceRoutingNode {
            @display("p=1441,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 426;
        }
        d17: SourceRoutingNode {
            @display("p=1478,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 417;
        }
        d27: SourceRoutingNode {
            @display("p=1478,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 427;
        }
        d18: SourceRoutingNode {
            @display("p=1512,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 418;
        }
        d28: SourceRoutingNode {
            @display("p=1512,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 428;
        }
        d19: SourceRoutingNode {
            @display("p=1547,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 419;
        }
        d29: SourceRoutingNode {
            @display("p=1547,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 429;
        }





        e01: SourceRoutingNode {
            @display("p=1575,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 501;
        }
        e02: SourceRoutingNode {
            @display("p=1609,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 502;
        }
        e11: SourceRoutingNode {
            @display("p=1645,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 511;
        }
        e21: SourceRoutingNode {
            @display("p=1645,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 521;
        }
        e12: SourceRoutingNode {
            @display("p=1683,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 512;
        }
        e22: SourceRoutingNode {
            @display("p=1683,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 522;
        }
        e13: SourceRoutingNode {
            @display("p=1722,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 513;
        }
        e23: SourceRoutingNode {
            @display("p=1722,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 523;
        }
        e14: SourceRoutingNode {
            @display("p=1760,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 514;
        }
        e24: SourceRoutingNode {
            @display("p=1760,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 524;
        }
        e15: SourceRoutingNode {
            @display("p=1799,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 515;
        }
        e25: SourceRoutingNode {
            @display("p=1799,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 525;
        }
        e16: SourceRoutingNode {
            @display("p=1834,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 516;
        }
        e26: SourceRoutingNode {
            @display("p=1834,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 526;
        }
        e17: SourceRoutingNode {
            @display("p=1871,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 517;
        }
        e27: SourceRoutingNode {
            @display("p=1871,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 527;
        }
        e18: SourceRoutingNode {
            @display("p=1905,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 518;
        }
        e28: SourceRoutingNode {
            @display("p=1905,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 528;
        }
        e19: SourceRoutingNode {
            @display("p=1940,65;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 519;
        }
        e29: SourceRoutingNode {
            @display("p=1940,151;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 529;
        }







        f01: SourceRoutingNode {
            @display("p=1974,106;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 601;
        }
        f02: SourceRoutingNode {
            @display("p=1974,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 602;
        }
        f21: SourceRoutingNode {
            @display("p=1940,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 621;
        }
        f11: SourceRoutingNode {
            @display("p=1940,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 611;
        }
        f12: SourceRoutingNode {
            @display("p=1905,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 612;
        }
        f22: SourceRoutingNode {
            @display("p=1905,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 622;
        }
        f13: SourceRoutingNode {
            @display("p=1871,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 613;
        }
        f23: SourceRoutingNode {
            @display("p=1871,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 623;
        }
        f14: SourceRoutingNode {
            @display("p=1834,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 614;
        }
        f24: SourceRoutingNode {
            @display("p=1834,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 624;
        }
        f15: SourceRoutingNode {
            @display("p=1799,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 615;
        }
        f25: SourceRoutingNode {
            @display("p=1799,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 625;
        }
        f16: SourceRoutingNode {
            @display("p=1760,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 616;
        }
        f26: SourceRoutingNode {
            @display("p=1760,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 626;
        }
        f17: SourceRoutingNode {
            @display("p=1722,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 617;
        }
        f27: SourceRoutingNode {
            @display("p=1722,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 627;
        }
        f18: SourceRoutingNode {
            @display("p=1683,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 618;
        }
        f28: SourceRoutingNode {
            @display("p=1683,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 628;
        }
        f19: SourceRoutingNode {
            @display("p=1645,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 619;
        }
        f29: SourceRoutingNode {
            @display("p=1645,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 629;
        }


        g01: SourceRoutingNode {
            @display("p=1609,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 701;
        }
        g02: SourceRoutingNode {
            @display("p=1575,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 702;
        }
        g21: SourceRoutingNode {
            @display("p=1547,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 721;
        }
        g11: SourceRoutingNode {
            @display("p=1547,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 711;
        }
        g12: SourceRoutingNode {
            @display("p=1512,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 712;
        }
        g22: SourceRoutingNode {
            @display("p=1512,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 722;
        }
        g13: SourceRoutingNode {
            @display("p=1478,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 713;
        }
        g23: SourceRoutingNode {
            @display("p=1478,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 723;
        }
        g14: SourceRoutingNode {
            @display("p=1441,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 714;
        }
        g24: SourceRoutingNode {
            @display("p=1441,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 724;
        }
        g15: SourceRoutingNode {
            @display("p=1406,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 715;
        }
        g25: SourceRoutingNode {
            @display("p=1406,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 725;
        }
        g16: SourceRoutingNode {
            @display("p=1367,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 716;
        }
        g26: SourceRoutingNode {
            @display("p=1367,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 726;
        }
        g17: SourceRoutingNode {
            @display("p=1329,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 717;
        }
        g27: SourceRoutingNode {
            @display("p=1329,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 727;
        }
        g18: SourceRoutingNode {
            @display("p=1290,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 718;
        }
        g28: SourceRoutingNode {
            @display("p=1290,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 728;
        }
        g19: SourceRoutingNode {
            @display("p=1252,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 719;
        }
        g29: SourceRoutingNode {
            @display("p=1252,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 729;
        }



        h01: SourceRoutingNode {
            @display("p=1212,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 801;
        }
        h02: SourceRoutingNode {
            @display("p=1175,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 802;
        }
        h21: SourceRoutingNode {
            @display("p=1147,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 821;
        }
        h11: SourceRoutingNode {
            @display("p=1147,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 811;
        }
        h12: SourceRoutingNode {
            @display("p=1112,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 812;
        }
        h22: SourceRoutingNode {
            @display("p=1112,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 822;
        }
        h13: SourceRoutingNode {
            @display("p=1078,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 813;
        }
        h23: SourceRoutingNode {
            @display("p=1078,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 823;
        }
        h14: SourceRoutingNode {
            @display("p=1041,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 814;
        }
        h24: SourceRoutingNode {
            @display("p=1041,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 824;
        }
        h15: SourceRoutingNode {
            @display("p=1006,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 815;
        }
        h25: SourceRoutingNode {
            @display("p=1006,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 825;
        }
        h16: SourceRoutingNode {
            @display("p=967,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 816;
        }
        h26: SourceRoutingNode {
            @display("p=967,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 826;
        }
        h17: SourceRoutingNode {
            @display("p=929,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 817;
        }
        h27: SourceRoutingNode {
            @display("p=929,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 827;
        }
        h18: SourceRoutingNode {
            @display("p=890,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 818;
        }
        h28: SourceRoutingNode {
            @display("p=890,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 828;
        }
        h19: SourceRoutingNode {
            @display("p=852,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 819;
        }
        h29: SourceRoutingNode {
            @display("p=852,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 829;
        }


        i01: SourceRoutingNode {
            @display("p=812,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 901;
        }
        i02: SourceRoutingNode {
            @display("p=780,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 902;
        }
        i21: SourceRoutingNode {
            @display("p=752,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 921;
        }
        i11: SourceRoutingNode {
            @display("p=752,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 911;
        }
        i12: SourceRoutingNode {
            @display("p=717,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 912;
        }
        i22: SourceRoutingNode {
            @display("p=717,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 922;
        }
        i13: SourceRoutingNode {
            @display("p=683,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 913;
        }
        i23: SourceRoutingNode {
            @display("p=683,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 923;
        }
        i14: SourceRoutingNode {
            @display("p=646,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 914;
        }
        i24: SourceRoutingNode {
            @display("p=646,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 924;
        }
        i15: SourceRoutingNode {
            @display("p=611,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 915;
        }
        i25: SourceRoutingNode {
            @display("p=611,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 925;
        }
        i16: SourceRoutingNode {
            @display("p=572,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 916;
        }
        i26: SourceRoutingNode {
            @display("p=572,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 926;
        }
        i17: SourceRoutingNode {
            @display("p=534,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 917;
        }
        i27: SourceRoutingNode {
            @display("p=534,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 927;
        }
        i18: SourceRoutingNode {
            @display("p=495,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 918;
        }
        i28: SourceRoutingNode {
            @display("p=495,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 928;
        }
        i19: SourceRoutingNode {
            @display("p=457,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 919;
        }
        i29: SourceRoutingNode {
            @display("p=457,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 929;
        }



        j01: SourceRoutingNode {
            @display("p=417,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1001;
        }
        j02: SourceRoutingNode {
            @display("p=384,296;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1002;
        }
        j21: SourceRoutingNode {
            @display("p=356,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1021;
        }
        j11: SourceRoutingNode {
            @display("p=356,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1011;
        }
        j12: SourceRoutingNode {
            @display("p=321,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1012;
        }
        j22: SourceRoutingNode {
            @display("p=321,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1022;
        }
        j13: SourceRoutingNode {
            @display("p=287,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1013;
        }
        j23: SourceRoutingNode {
            @display("p=287,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1023;
        }
        j14: SourceRoutingNode {
            @display("p=250,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1014;
        }
        j24: SourceRoutingNode {
            @display("p=250,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1024;
        }
        j15: SourceRoutingNode {
            @display("p=215,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1015;
        }
        j25: SourceRoutingNode {
            @display("p=215,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1025;
        }
        j16: SourceRoutingNode {
            @display("p=176,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1016;
        }
        j26: SourceRoutingNode {
            @display("p=176,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1026;
        }
        j17: SourceRoutingNode {
            @display("p=138,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1017;
        }
        j27: SourceRoutingNode {
            @display("p=138,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1027;
        }
        j18: SourceRoutingNode {
            @display("p=99,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1018;
        }
        j28: SourceRoutingNode {
            @display("p=99,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1028;
        }
        j19: SourceRoutingNode {
            @display("p=61,336;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1019;
        }
        j29: SourceRoutingNode {
            @display("p=61,255;b=15,15,oval,#868686,,1;tt=q;i=misc/node2,#676767,100;is=vs");
            address = 1029;
        }

    connections:


        a01.port++ <--> C <--> a02.port++;
        a02.port++ <--> C <--> a11.port++;
        a02.port++ <--> C <--> a21.port++;
        a11.port++ <--> C <--> a12.port++;
        a21.port++ <--> C <--> a22.port++;
        a12.port++ <--> C <--> a13.port++;
        a22.port++ <--> C <--> a23.port++;
        a13.port++ <--> C <--> a14.port++;
        a23.port++ <--> C <--> a24.port++;
        a14.port++ <--> C <--> a15.port++;
        a24.port++ <--> C <--> a25.port++;
        a15.port++ <--> C <--> a16.port++;
        a25.port++ <--> C <--> a26.port++;
        a16.port++ <--> C <--> a17.port++;
        a26.port++ <--> C <--> a27.port++;
        a17.port++ <--> C <--> a18.port++;
        a27.port++ <--> C <--> a28.port++;
        b01.port++ <--> C <--> b02.port++;
        b02.port++ <--> C <--> b11.port++;
        b02.port++ <--> C <--> b21.port++;
        b11.port++ <--> C <--> b12.port++;
        b21.port++ <--> C <--> b22.port++;
        b12.port++ <--> C <--> b13.port++;
        b22.port++ <--> C <--> b23.port++;
        b13.port++ <--> C <--> b14.port++;
        b23.port++ <--> C <--> b24.port++;
        b14.port++ <--> C <--> b15.port++;
        b24.port++ <--> C <--> b25.port++;
        b15.port++ <--> C <--> b16.port++;
        b25.port++ <--> C <--> b26.port++;
        b16.port++ <--> C <--> b17.port++;
        b26.port++ <--> C <--> b27.port++;
        b17.port++ <--> C <--> b18.port++;
        b27.port++ <--> C <--> b28.port++;
        c01.port++ <--> C <--> c02.port++;
        a18.port++ <--> C <--> a19.port++;
        a28.port++ <--> C <--> a29.port++;
        a19.port++ <--> C <--> b01.port++;
        a29.port++ <--> C <--> b01.port++;
        b18.port++ <--> C <--> b19.port++;
        b28.port++ <--> C <--> b29.port++;
        b19.port++ <--> C <--> c01.port++;
        b29.port++ <--> C <--> c01.port++;
        c02.port++ <--> C <--> c11.port++;
        c02.port++ <--> C <--> c21.port++;
        c11.port++ <--> C <--> c12.port++;
        c21.port++ <--> C <--> c22.port++;
        c12.port++ <--> C <--> c13.port++;
        c22.port++ <--> C <--> c23.port++;
        c13.port++ <--> C <--> c14.port++;
        c23.port++ <--> C <--> c24.port++;
        c14.port++ <--> C <--> c15.port++;
        c24.port++ <--> C <--> c25.port++;
        c15.port++ <--> C <--> c16.port++;
        c25.port++ <--> C <--> c26.port++;
        c16.port++ <--> C <--> c17.port++;
        c26.port++ <--> C <--> c27.port++;
        c17.port++ <--> C <--> c18.port++;
        c27.port++ <--> C <--> c28.port++;
        c18.port++ <--> C <--> c19.port++;
        c28.port++ <--> C <--> c29.port++;
        c19.port++ <--> C <--> d01.port++;
        c29.port++ <--> C <--> d01.port++;
        d01.port++ <--> C <--> d02.port++;
        d02.port++ <--> C <--> d11.port++;
        d02.port++ <--> C <--> d21.port++;
        d11.port++ <--> C <--> d12.port++;
        d21.port++ <--> C <--> d22.port++;
        d12.port++ <--> C <--> d13.port++;
        d22.port++ <--> C <--> d23.port++;
        d13.port++ <--> C <--> d14.port++;
        d23.port++ <--> C <--> d24.port++;
        d14.port++ <--> C <--> d15.port++;
        d24.port++ <--> C <--> d25.port++;
        d15.port++ <--> C <--> d16.port++;
        d25.port++ <--> C <--> d26.port++;
        d16.port++ <--> C <--> d17.port++;
        d26.port++ <--> C <--> d27.port++;
        d17.port++ <--> C <--> d18.port++;
        d27.port++ <--> C <--> d28.port++;
        d18.port++ <--> C <--> d19.port++;
        d28.port++ <--> C <--> d29.port++;
        d19.port++ <--> C <--> e01.port++;
        d29.port++ <--> C <--> e01.port++;
        e01.port++ <--> C <--> e02.port++;
        e02.port++ <--> C <--> e11.port++;
        e02.port++ <--> C <--> e21.port++;
        e11.port++ <--> C <--> e12.port++;
        e21.port++ <--> C <--> e22.port++;
        e12.port++ <--> C <--> e13.port++;
        e22.port++ <--> C <--> e23.port++;
        e13.port++ <--> C <--> e14.port++;
        e23.port++ <--> C <--> e24.port++;
        e14.port++ <--> C <--> e15.port++;
        e24.port++ <--> C <--> e25.port++;
        e15.port++ <--> C <--> e16.port++;
        e25.port++ <--> C <--> e26.port++;
        e16.port++ <--> C <--> e17.port++;
        e26.port++ <--> C <--> e27.port++;
        e17.port++ <--> C <--> e18.port++;
        e27.port++ <--> C <--> e28.port++;
        e18.port++ <--> C <--> e19.port++;
        e28.port++ <--> C <--> e29.port++;
        e19.port++ <--> C <--> f01.port++;
        e29.port++ <--> C <--> f01.port++;
        f01.port++ <--> C <--> f02.port++;
        f02.port++ <--> C <--> f21.port++;
        f02.port++ <--> C <--> f11.port++;
        f21.port++ <--> C <--> f22.port++;
        f11.port++ <--> C <--> f12.port++;
        f22.port++ <--> C <--> f23.port++;
        f12.port++ <--> C <--> f13.port++;
        f23.port++ <--> C <--> f24.port++;
        f13.port++ <--> C <--> f14.port++;
        f24.port++ <--> C <--> f25.port++;
        f14.port++ <--> C <--> f15.port++;
        f25.port++ <--> C <--> f26.port++;
        f15.port++ <--> C <--> f16.port++;
        f26.port++ <--> C <--> f27.port++;
        f16.port++ <--> C <--> f17.port++;
        f27.port++ <--> C <--> f28.port++;
        f17.port++ <--> C <--> f18.port++;
        f28.port++ <--> C <--> f29.port++;
        f18.port++ <--> C <--> f19.port++;

        f29.port++ <--> C <--> g01.port++;
        f19.port++ <--> C <--> g01.port++;
        g01.port++ <--> C <--> g02.port++;
        g02.port++ <--> C <--> g21.port++;
        g02.port++ <--> C <--> g11.port++;
        g21.port++ <--> C <--> g22.port++;
        g11.port++ <--> C <--> g12.port++;
        g22.port++ <--> C <--> g23.port++;
        g12.port++ <--> C <--> g13.port++;
        g23.port++ <--> C <--> g24.port++;
        g13.port++ <--> C <--> g14.port++;
        g24.port++ <--> C <--> g25.port++;
        g14.port++ <--> C <--> g15.port++;
        g25.port++ <--> C <--> g26.port++;
        g15.port++ <--> C <--> g16.port++;
        g26.port++ <--> C <--> g27.port++;
        g16.port++ <--> C <--> g17.port++;
        g27.port++ <--> C <--> g28.port++;
        g17.port++ <--> C <--> g18.port++;
        g28.port++ <--> C <--> g29.port++;
        g18.port++ <--> C <--> g19.port++;

        g29.port++ <--> C <--> h01.port++;
        g19.port++ <--> C <--> h01.port++;
        h01.port++ <--> C <--> h02.port++;
        h02.port++ <--> C <--> h21.port++;
        h02.port++ <--> C <--> h11.port++;
        h21.port++ <--> C <--> h22.port++;
        h11.port++ <--> C <--> h12.port++;
        h22.port++ <--> C <--> h23.port++;
        h12.port++ <--> C <--> h13.port++;
        h23.port++ <--> C <--> h24.port++;
        h13.port++ <--> C <--> h14.port++;
        h24.port++ <--> C <--> h25.port++;
        h14.port++ <--> C <--> h15.port++;
        h25.port++ <--> C <--> h26.port++;
        h15.port++ <--> C <--> h16.port++;
        h26.port++ <--> C <--> h27.port++;
        h16.port++ <--> C <--> h17.port++;
        h27.port++ <--> C <--> h28.port++;
        h17.port++ <--> C <--> h18.port++;
        h28.port++ <--> C <--> h29.port++;
        h18.port++ <--> C <--> h19.port++;

        h29.port++ <--> C <--> i01.port++;
        h19.port++ <--> C <--> i01.port++;
        i01.port++ <--> C <--> i02.port++;
        i02.port++ <--> C <--> i21.port++;
        i02.port++ <--> C <--> i11.port++;
        i21.port++ <--> C <--> i22.port++;
        i11.port++ <--> C <--> i12.port++;
        i22.port++ <--> C <--> i23.port++;
        i12.port++ <--> C <--> i13.port++;
        i23.port++ <--> C <--> i24.port++;
        i13.port++ <--> C <--> i14.port++;
        i24.port++ <--> C <--> i25.port++;
        i14.port++ <--> C <--> i15.port++;
        i25.port++ <--> C <--> i26.port++;
        i15.port++ <--> C <--> i16.port++;
        i26.port++ <--> C <--> i27.port++;
        i16.port++ <--> C <--> i17.port++;
        i27.port++ <--> C <--> i28.port++;
        i17.port++ <--> C <--> i18.port++;
        i28.port++ <--> C <--> i29.port++;
        i18.port++ <--> C <--> i19.port++;

        i29.port++ <--> C <--> j01.port++;
        i19.port++ <--> C <--> j01.port++;
        j01.port++ <--> C <--> j02.port++;
        j02.port++ <--> C <--> j21.port++;
        j02.port++ <--> C <--> j11.port++;
        j21.port++ <--> C <--> j22.port++;
        j11.port++ <--> C <--> j12.port++;
        j22.port++ <--> C <--> j23.port++;
        j12.port++ <--> C <--> j13.port++;
        j23.port++ <--> C <--> j24.port++;
        j13.port++ <--> C <--> j14.port++;
        j24.port++ <--> C <--> j25.port++;
        j14.port++ <--> C <--> j15.port++;
        j25.port++ <--> C <--> j26.port++;
        j15.port++ <--> C <--> j16.port++;
        j26.port++ <--> C <--> j27.port++;
        j16.port++ <--> C <--> j17.port++;
        j27.port++ <--> C <--> j28.port++;
        j17.port++ <--> C <--> j18.port++;
        j28.port++ <--> C <--> j29.port++;
        j18.port++ <--> C <--> j19.port++;
        j29.port++ <--> C <--> a00.port++;
        j19.port++ <--> C <--> a00.port++;
        a00.port++ <--> C <--> a01.port++;
}

