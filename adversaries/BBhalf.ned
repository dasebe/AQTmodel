
package adversarialqueueing.adversaries;

//
// Adversary
//
simple BBhalf like AdvancedAdversary
{
	double timeSlotLength @unit(s) = default(1ms); // time between generating packets
        int frameCapacity = default(1000); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        int initialSetSize = default(100); // initial set size
        double injectionRate = default(1); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
	double injectionRandSTDTime; // set standard deviation of how much injections may deviate from scheduled time
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
	@statistic[injectionTime](title="injectionTime";record=vector?;interpolationmode=sample-hold);
    gates:
        inout adversaryControl @loose;
}


