//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package adversaries;

//
// Application model to generate traffic for the network.
//
simple CE7Adversary like IAdversary
{
    parameters:
		volatile double sendIaTime @unit(s) = default(10ms); // time between generating packets
        int frameCapacity = default(1000); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        volatile double injectionRate = default(1); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
    gates:
        output adversaryControl @loose;
}


