#include <omnetpp.h>
#include <distrib.h>

class VDrChannel : public cDatarateChannel
{
  protected:
    int scale;
    int shape;
    int datarate;
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
    const char *vstr = par("weibull").stringValue(); // e.g. "1.0227 24.95" which means "scale shape"
    std::vector<double> v = cStringTokenizer(vstr).asDoubleVector();
    shape = v.back();
    v.pop_back();
    scale = v.back();
    v.pop_back();
    datarate = par("datarate");
    if(shape != 0) {
        cDatarateChannel::setDatarate(weibull(scale,shape)*datarate);
    }
}

void VDrChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t, result);
    if(shape != 0) {
        //double nextDatarate = truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001; //in expectancy this will result in meanDr = mean, however, no 0 values will occur
        double nextDatarate = weibull(scale,shape)*datarate; //weibull(scale,shape)
        cDatarateChannel::setDatarate(nextDatarate);
    }
}
