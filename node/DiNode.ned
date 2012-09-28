
package adversarialqueueing.node;

//
// DEPRECATED
// Old approach to directed graphs in omnet.
// A "Node" consists of a Routing plus an App module which represents the
// aggregate traffic of the subnets connected to that router.
//
module DiNode
{
    parameters:
        int address;
        string appType;
        @display("i=misc/node_vs,gold;bgb=352,317");
    gates:
        input ingress[];
        output egress[];
    submodules:
        app: <appType> like IApp {
            parameters:
                address = address;
                @display("p=98,69");
        }
        routing: SourceRouting {
            parameters:
                @display("p=98,218");
            gates:
                in[sizeof(ingress)];
                out[sizeof(egress)];
        }
        //FIXME
        //DOESNT WORK DUE TO L2Queue Implementation: use Queue or own module instead
        queue[sizeof(egress)]: L2Queue {
            parameters:
                @display("p=187,218,row");
        }
    connections:
        //routing <-> app
        routing.localOut --> app.in;
        routing.localIn <-- app.out;
        // ingress port -> routing in
        for i=0..sizeof(ingress)-1 {
            routing.in[i] <-- ingress[i];
        }
        // egress port <- queue <- routing out
        for i=0..sizeof(egress)-1 {
            routing.out[i] --> queue[i].in;
            queue[i].out --> egress[i];
        }
}


