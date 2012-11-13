
package adversarialqueueing.adversaries;

simple Randomization
{
    parameters:
		volatile double meandelay @unit(s) = default(1ms); //target mean
		volatile double stddelay @unit(s) = default(500us);
		volatile double sendIaTime @unit(s) = default(1ms); // time slot
}


