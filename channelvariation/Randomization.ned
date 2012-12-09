package adversarialqueueing.channelvariation;

simple Randomization
{
    parameters:
		volatile double meanrate @unit(bps) = default(10Mbps); //target mean
		volatile double stdrate @unit(bps) = default(0bps);
		volatile double timeSlotLength @unit(s) = default(1ms); // time slot
}


