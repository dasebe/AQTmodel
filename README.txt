
Documentation of the adversarial queueing omnet package

1. Overview

On paper adversarial queueing relies on directed graphs and routing paths determined by list of edges/links which a packet needs to visit.
However, most network connection work bidirectional and do not support link-level addressing.
This simulations adapts a source routing approach (similar to IP loose source routing): packets hold an ordered list of nodes to visit. Once the current destination is reached the corresponding router or node will check if any further destination remains and update the current destination accordingly. If no further destination remains the packet is absorbed by delivering it to an upper layer.

2. Nodes

Each node (SourceRoutingNode) in this omnet package is implemented as a compound module and comprises three layers: queue, routing, and application layer.

Any interaction with links happens via the L2Queue module from the omnet routing example. 
No delays are added on arriving packets - they are delivered to the routing layer in the same timestep. Outgoing packets will be buffered if the link is busy until the configuration parameter $framesize is exceed. Packets arriving on a queue with length equal to $framesize occur as loss to the system.

The routing layer (SourceRouting) bases routing decisions on a static precomputet shortest-path routing table. Source routing destinations are arrays in inverse order, so that the current destination is last. Upon arrival at an intermediate router, the array size is reduced by one and the packet forwarded towards the corresponding next hop according to the routing table. Although loose source routing is fully supported, for clarity purposes each hop is usually determined in adversarial instability examples.

The SourceRoutingApp symbolizes the application layer and is assumed to be under control of the adversary. That is, the adversary can send directly ("over the air") injection commands (InjectionCommandMessages) to each node resulting in the faithful injection of new packets into the Apps routing layer.
Injection constraints due to the adversarial queueing model are not enforced neither be syntaxed nor static checks. In fact, this simulation only facilitates only manual checking and assumes this is done on paper before using this software.
 
As the adversary needs queue length information to synchronize with the current network state (to maximize efficiency) it is allowed to query two (implementation restriction) queues for their length usually at the start of a new phase.

3. Adversaries

Adversaries are subclassed from the AdvancedAdversary type which implements a lot of functionality shared amongst all previously encountered adversary types.
An adversary consists of an initialization routine which sets up the to be queried queues, some environmental parameters (depending on network topology), and injects the initial packets.
As omnet++ is an event-based simulator, also an adversaries inner synchronization works in an event-based manner.
After the initial packets have been injected a special self-message is scheduled at simulation start to start a "phase" which is one series of injections that constitute each one step of the overall inductive process.
This phase comprises three subphases.
First the current network state is queried, then injection command are send to the network nodes, and finally the next phase is prepared which usually takes part in a symmetric part of the network.

The current network is obtained from QueueListener objects which are usually set up in the initilization and then listen to any event of the configured queues
 to learn their current length.

Injections command are send in a two step manner. First (on a user side) they are specified as sets, i.e., n packets are injected at node x with path vector y with inter-injection time 1/r. Then in a second step the AdvancedAdversary class translates this request in many separate injection commands which are then scheduled at the calculated time steps and sent to the corresponding network nodes for injection.

Preparing the next phase is in implementation up to an adversary designer. A dumb approach names the symmetric parts in a network similarly in a structured way so that by simple string modification different phases translate into the same representation.
Then the start of a new phase is scheduled according to the adversary definition. This might just after the last injections of one phase happened (as for the Baseball network) or even be interleaved with injection from the still active phase (e.g. in CE7 type adversaries). 

4. Package Structure

./omnetpp.ini           file to store configuration parameters for different runs
./adversarialQueueing   symbolic link to simulation binary
./messages              message/packet classes (usually automatically constructed by omnet from .msg description file)
./results               output directory where result vectors (.vec), scalars (.sca) and meta information (.vci) is stored
./node                  all parts of node compound module go here, each separated into ned omnet file, and corresponding c++ class 
./networks              omnet++ ned representation of available networks
./out                   binary files
./adversaries           definition of adversaries and their meta and helper classes
./resultAnalysis        save folder for analysization models of result files either in scave (.anf) or R (.R)

5. Statistic Recording and Evaluation

some relevant recorded statistics are
 - the total number of injections
 - end-2-end delay vectors for each destination
 - overall loss scalar for each queue
 - qlen vector for each queue
 
Evaluation can be either done in scave (from the omnet++ distribution) or R with the r-omnet extension.
Use scave for quick overview statistics as it's quite fast, has an accessible gui and access to all the data.
For advanced aggregation and statistic questions R seems an easier choice.
See for example the computation of loss graphs in resultAnalysis/results.R