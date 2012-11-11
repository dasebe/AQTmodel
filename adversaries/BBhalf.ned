
package adversarialqueueing.adversaries;

//
// Adversary
//
simple BBhalf like AdvancedAdversary
{
    parameters:
		volatile double sendIaTime @unit(s) = default(10ms); // time between generating packets
        int frameCapacity = default(1000); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        int initialSetSize = default(100); // initial set size
        volatile double injectionRate = default(1); // L2Queue frame capacity (default value is not meaningful, but means infinite queue for L2Queue)
        @signal[injectedPackets](type="long");
        @statistic[injectedPackets](title="injected Packets"; interpolationmode=none; record=count);
    gates:
        inout adversaryControl @loose;
}


