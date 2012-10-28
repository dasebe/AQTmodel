package adversarialqueueing.adversaries;

//
// Adversary for CE3
//
simple CF3 like AdvancedAdversary
{
    parameters:
		volatile double sendIaTime @unit(s) = default(10ms); // time between generating packets
        int frameCapacity = default(1000); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        volatile double injectionRate = default(1); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
    gates:
        inout adversaryControl @loose; //for direct control of nodes, their routing, and for getting feedback on network state
}


