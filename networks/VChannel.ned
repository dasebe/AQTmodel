package adversarialqueueing.networks;

channel VChannel extends ned.DelayChannel
{
    @class(VChannel);
	int deviation @unit("s") = default(0s); //standard deviation of delay
	delay @unit("s") = default(1ms); //mean delay
}
