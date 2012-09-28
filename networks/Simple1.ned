//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package networks;

import node.SourceRoutingNode;
import ned.DatarateChannel;

//
// A ten-node network topology
//
network Simple1
{
    types:
        channel C extends DatarateChannel
        {
            delay = 1ms;
            //delay = uniform(0.1ms, 1ms);
            datarate = 1Mbps;
        }
    submodules:
        vtx[5]: SourceRoutingNode {
            address = index;
        }
    connections:
        vtx[0].port++ <--> C <--> vtx[1].port++;
        vtx[1].port++ <--> C <--> vtx[2].port++;
        vtx[2].port++ <--> C <--> vtx[3].port++;
        vtx[3].port++ <--> C <--> vtx[4].port++;
        vtx[4].port++ <--> C <--> vtx[0].port++;
//        vtx[0].egress++ --> C --> vtx[1].ingress++;
//        vtx[1].egress++ --> C --> vtx[2].ingress++;
//        vtx[2].egress++ --> C --> vtx[3].ingress++;
//        vtx[3].egress++ --> C --> vtx[4].ingress++;
//        vtx[4].egress++ --> C --> vtx[0].ingress++;
}

