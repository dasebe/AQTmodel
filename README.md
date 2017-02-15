# Adversarial Queueing Framework for OMNeT++ 4.5

The AQTmodel is an open-source framework to simulate unstable queueing scenarios in the framework of Adversarial Queueing Theory [1],[4] and Adversarial Queueing with finite buffers and timing variations [3].

The focus of this network simulator is to study (network) packet loss in various instability scenarios.
Some topologies and adversaries are implemented as C++ classes and available for immediate use.
 - the baseball graph by Andrews et al. [5], which is unstable for r>0.85
 - the smallest example for the graph minor class A+ by Weinard [2], which is unstable for r>0.933
 - the graph introduced by Diaz et al. [8], which is unstable for r>0.83
 - the parameterized gadget-chain by Lotker et al. [7], which is unstable for r>0.5


IMPORTANT: The AQTmodel is still in an early immature state. Do not hesitate to contact us and report unexpected behavior.
Not all parts and possible parameterizations have been tested. In case of using this framework for any other purpose than for your self: it is your responsibility to make sure that the model works correctly and produces valid results.


## GETTING STARTED

Start by downloading and installing OMNeT++ in version at least 4.5.
(http://www.omnetpp.org/).
Introduce yourself to the OMNeT world with the samples from the original OMNeT framework. The adversarial scenarios proposed here are not yet easily accessible and need some understanding of the whole framework.

### Directory structure

 - ./omnetpp.ini		main configuration file, store configuration parameters for different runs
 - ./adversarialQueueing 	symbolic link to main executable (don't forget to add omnet to your path variable!)
 - ./messages 		messages used for component internal communication and actual network packets
 - ./node 		       	network nodes are composed of three layers, corresponding classes are here
 - ./networks 		OMNeT++ ned representation of available networks
 - ./adversaries 		super class AdvancedAversary and subclasses which are examples of adversary implementations
 - ./channelvariation	you may use OMNeT DelayChannel or DatarateChannel for deterministic AQT simulations (make sure that the time step length is matched by link traversal time; this folder gives the additional possibility to model a channel's capacity variation over time

To implement a new scenario, we suggest that you copy-paste from the Baseball graph which has been repeatedly studied in the literature before.
For result analysis we encourage to use the omnetpp R package in at least version 0.2. You may ask for an R skeleton for AQT analysis by email to the authors.

## REFERENCES

 1. A. Borodin, J. Kleinberg, P. Raghavan, M. Sudan, and D. P. Williamson. Adversarial queuing theory. Journal of the ACM, 48(1):13–38, Jan. 2001.
 2. M. Weinard. Deciding the FIFO stability of networks in polynomial time. Algorithms and Complexity, (3):81–92, 2006.
 3. DS. Berger, M. Karsten, J. Schmitt. On the Relevance of Adversarial Queueing Theory in Practice, In ACM SIGMETRICS, pages 343-354, 2014.
 4. DS. Berger, M. Karsten, and J. Schmitt. Simulation of Adversarial Scenarios in OMNeT ++ – Putting Adversarial Queueing Theory from Its Head to Feet. In Proc. of the ICST Conference on Simulation Tools and Techniques, 2013.
 5. M. Andrews, B. Awerbuch, A. Fernandez, T. Leighton, Z. Liu, and J. Kleinberg. Universal-stability results and performance bounds for greedy contention-resolution protocols. Journal of the ACM, 48(1):39–69, Jan. 2001.
 6. R. Bhattacharjee and A. Goel. Instability of FIFO at Arbitrarily Low Rates in the Adversarial Queueing Model. SIAM Journal on Computing, 34(2):318, 2005.
 7. Z. Lotker, B. Patt-Shamir, and A. Rosen. New Stability Results for Adversarial Queuing. SIAM Journal on Computing, 33(2):286, 2004.
 8. J. Diaz, D. Koukopoulos, S. Nikoletseas, M. Serna, P. Spirakis, and D. M. Thilikos. Stability and  non-stability of the FIFO protocol. In Proc. of the SPAA, pages 48–52, Crete Island, Greece, 2001. ACM.
Projects