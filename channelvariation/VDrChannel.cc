#include <omnetpp.h>
#include <distrib.h>

class VDrChannel : public cDatarateChannel
{
  protected:
    int scale;
    int shape;
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
    scale = par("scale");
    shape = par("shape");
    cDatarateChannel::setDatarate(
            truncnormal(scale-0.0001,shape)+0.0001);
}

void VDrChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t, result);
    if(shape != 0) {
        //double nextDatarate = truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001; //in expectancy this will result in meanDr = mean, however, no 0 values will occur
        double nextDatarate = weibull(scale,shape); //weibull(scale,shape)
        cDatarateChannel::setDatarate(nextDatarate);
    }
}
