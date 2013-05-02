
package adversarialqueueing.adversaries;

//
// Adversary for circular CE7 
//
simple CE7 like AdvancedAdversary
{
    parameters:
	double timeSlotLength @unit(s) = default(1ms); // time between generating packets
        int frameCapacity = default(1000); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        int initialSetSize = default(100); // initial set size
        double injectionRate = default(1); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
	string gaussianInjTime; // set standard deviation of how much injections may deviate from scheduled time
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
        @statistic[measuredSetSize](title="measuredSetSize";record=vector?;interpolationmode=sample-hold);
	@statistic[injectionTime](title="injectionTime";record=vector?;interpolationmode=sample-hold);
    gates:
        inout adversaryControl @loose; //for direct control of nodes, their routing, and for getting feedback on network state
}


