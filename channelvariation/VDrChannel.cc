#include <omnetpp.h>
#include <distrib.h>

class VDrChannel : public cDatarateChannel
{
  protected:
    int meanDatarate;
    int stdDatarate;
  public:
    explicit VDrChannel(const char *name = NULL);
    virtual ~VDrChannel();
    virtual void initialize();
    virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
};

Register_Class(VDrChannel);

VDrChannel::VDrChannel(const char *name) : cDatarateChannel(name)
{
}

VDrChannel::~VDrChannel()
{
}

void VDrChannel::initialize()
{
    cDatarateChannel::initialize();
    meanDatarate = par("meanDatarate");
    stdDatarate = par("stdDatarate");
    cDatarateChannel::setDatarate(
            truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001);
}

void VDrChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t, result);
    double nextDatarate = truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001;
    cDatarateChannel::setDatarate(nextDatarate);
    ev << "DR: " << nextDatarate;
}
