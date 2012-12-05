
package adversarialqueueing.adversaries;

simple RandomizationDelay
{
    parameters:
		volatile double meandelay @unit(s) = default(0.1ms); //target mean
		volatile double sendIaTime @unit(s) = default(1ms); // time slot
}


