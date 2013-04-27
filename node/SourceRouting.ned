
package adversarialqueueing.node;

//
// Omnet network model for source routing router.
//
simple SourceRouting
{
    parameters:
        @display("i=block/switch");
        @signal[drop](type="long");
        @signal[outputIf](type="int");
        @statistic[drop](title="dropped packet byte length";unit=bytes;record=vector?,count,sum;interpolationmode=none);
        @statistic[outputIf](title="output interface for each routed packet";record=histogram?;interpolationmode=none);
    gates:
        input in[];
        output out[];
        input localIn;
        output localOut;
        input adversaryControl @directIn; //for direct control of the adversary via cmessages
        
}


