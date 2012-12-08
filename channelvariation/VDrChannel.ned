package adversarialqueueing.channelvariation;
channel VDrChannel extends ned.DatarateChannel
{
    @class(VDrChannel);
	int meanDatarate @unit("bps") = default(10Mbps);
	int stdDatarate @unit("bps") = default(0bps); //standard deviation of delay
}
