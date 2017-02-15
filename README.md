# Adversarial Queueing Framework for OMNeT++ 4.5

The AQTmodel is an open-source framework to simulate unstable queueing scenarios in the framework of Adversarial Queueing Theory [1],[4] and Adversarial Queueing with finite buffers and timing variations [3].

The focus of this network simulator is to study (network) packet loss in various instability scenarios.
Some topologies and adversaries are implemented as C++ classes and available for immediate use.
 - the baseball graph by Andrews et al. [5], which is unstable for r>0.85
 - the smallest example for the graph minor class A+ by Weinard [2], which is unstable for r>0.933
 - the graph introduced by Diaz et al. [8], which is unstable for r>0.83
 - the parameterized gadget-chain by Lotker et al. [7], which is unstable for r>0.5

## A new perspective on adversarial queueing

This simulator provides a new perspective on adversarial queueing effects. It allows to investigate

 - the quantitative effects of adversarial queueing in finite buffer networks (-> loss)
 - with some asynchrony due to random effects in nodal processing and link delays, and
 - with timing variations for adversarial injections

Simulation results indicate that classical AQT examples appear harmless under realistic assumptions but for a novel class of adversaries considerably higher loss can be observed. This novel class introduces two new AQT concepts to construct loss-efficient network adversaries.

![image](https://cloud.githubusercontent.com/assets/9959772/22965845/ca41834e-f35f-11e6-8ef7-e8c0f96ba919.png)

The simulator also proves that the loss caused by classical adversaries (like the Baseball (BB) scenario) diminishes to irrelevant values in face of network randomization. The underlying model assumes that (instead of a deterministic network model with uniform and synchronized network links) each channel’s delay (the corresponding server delay for processing a single packet) follows a Weibull distributed random variable with mean one and various degrees of standard deviations up to 300%.

![image](https://cloud.githubusercontent.com/assets/9959772/22965861/daaf8a28-f35f-11e6-90ac-8d880b07b6f1.png)

The new class of network adversaries (shown here, the Reactive Adversary (RA)) proves robust against randomized de-synchronization effects both in terms of variable link delays and injection synchronization.

![image](https://cloud.githubusercontent.com/assets/9959772/22965863/de2e2b64-f35f-11e6-9047-db3f1469a80e.png)

## Getting started

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

## References

 1. A. Borodin, J. Kleinberg, P. Raghavan, M. Sudan, and D. P. Williamson. Adversarial queuing theory. Journal of the ACM, 48(1):13–38, Jan. 2001.
 2. M. Weinard. Deciding the FIFO stability of networks in polynomial time. Algorithms and Complexity, (3):81–92, 2006.
 3. DS. Berger, M. Karsten, J. Schmitt. On the Relevance of Adversarial Queueing Theory in Practice, In ACM SIGMETRICS, pages 343-354, 2014.
 4. DS. Berger, M. Karsten, and J. Schmitt. Simulation of Adversarial Scenarios in OMNeT ++ – Putting Adversarial Queueing Theory from Its Head to Feet. In Proc. of the ICST Conference on Simulation Tools and Techniques, 2013.
 5. M. Andrews, B. Awerbuch, A. Fernandez, T. Leighton, Z. Liu, and J. Kleinberg. Universal-stability results and performance bounds for greedy contention-resolution protocols. Journal of the ACM, 48(1):39–69, Jan. 2001.
 6. R. Bhattacharjee and A. Goel. Instability of FIFO at Arbitrarily Low Rates in the Adversarial Queueing Model. SIAM Journal on Computing, 34(2):318, 2005.
 7. Z. Lotker, B. Patt-Shamir, and A. Rosen. New Stability Results for Adversarial Queuing. SIAM Journal on Computing, 33(2):286, 2004.
 8. J. Diaz, D. Koukopoulos, S. Nikoletseas, M. Serna, P. Spirakis, and D. M. Thilikos. Stability and  non-stability of the FIFO protocol. In Proc. of the SPAA, pages 48–52, Crete Island, Greece, 2001. ACM.

## Disclaimer

The AQTmodel is still in an early immature state. Do not hesitate to contact us and report unexpected behavior.
Not all parts and possible parameterizations have been tested. In case of using this framework for any other purpose than for your self: it is your responsibility to make sure that the model works correctly and produces valid results.
