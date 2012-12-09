
package adversarialqueueing.adversaries;

//
// Adversary
//
moduleinterface AdvancedAdversary
{
    parameters:
		volatile double timeSlotLength @unit(s); // time between generating packets
        int frameCapacity; // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        int initialSetSize; // initial set size
        volatile double injectionRate; // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
        @statistic[measuredSetSize](title="measuredSetSize";record=vector;interpolationmode=sample-hold);
    gates:
        inout adversaryControl @loose; //for direct control of nodes, their routing, and for getting feedback on network state
}


