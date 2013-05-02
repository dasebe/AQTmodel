package adversarialqueueing.channelvariation;
channel VDrChannel extends ned.DatarateChannel
{
    @class(VDrChannel);
	string weibull; // (scale shape) parameter of weibull
    int packetLength @unit(byte) = default(1250 bytes);  // length of one message - used to compute target datarate
	double timeSlotLength @unit(s) = default(1 ms); // length of an AQT time step - used to compute target datarate
}
