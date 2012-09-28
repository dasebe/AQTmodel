
//
// This is the omnet message template for messages to be exchanged between network nodes.
// In order to exactly predetermine the path a packet takes through the network, this is implemented as source routing.
// The files
//  SourceRoutingPacket_m.h
//  SourceRoutingPacket_m.cc
// are automatically created from it. 
//

packet SourceRoutingPacket {
    int srcAddr;							//omnet address (int) of the packet's originator
    int destAddr[]; 					//array of nodes to visit, last one goes first (reversed order)
    int hopCount;							
    int recordRoute[];
}
