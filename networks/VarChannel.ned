package adversarialqueueing.networks;
import ned.DelayChannel;


channel VarChannel
{
	@class(VarChannel);
	int deviation @unit("s") = default(0s);
	double channelMeanDelay @unit("s") = default(1ms); // time between generating packets
}

