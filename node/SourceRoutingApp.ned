
package adversarialqueueing.node;

//
// Application layer for network nodes
//
simple SourceRoutingApp
{
    parameters:
        int address;  // local node address
        int packetLength @unit(byte) = default(1250 bytes);  // length of one message (fixed! no "volatile" modifier)
        @display("i=block/browser");
        @signal[endToEndDelay](type="simtime_t");
        @signal[hopCount](type="int");
        @signal[sourceAddress](type="int");
        @statistic[endToEndDelay](title="end-to-end delay of arrived packets"; unit=s; record=vector?,mean?,max?; interpolationmode=none);
        @statistic[hopCount](title="hop count of arrived packets"; interpolationmode=none; record=vector?,mean?,max?);
        @statistic[sourceAddress](title="source address of arrived packets"; interpolationmode=none; record=vector?);
    gates:
        input in;
        output out;
        input adversaryControl @directIn; //for direct control of the adversary via cmessages
}


