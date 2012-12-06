package adversarialqueueing.networks;

channel VarChannel
{
	parameters:
		double channelMeanDelay @unit(s) = default(1ms); // time between generating packets
		double delay @unit(s) = default(1ms); // time between generating packets
}

