#include <omnetpp.h>
#include <distrib.h>

class VDrChannel : public cDatarateChannel
{
  protected:
    double scale;
    double shape;
    int packetLength;
    double timeSlotLength;
    simsignal_t channelDelay;

  public:
    explicit VDrChannel(const char *name = NULL);
    virtual ~VDrChannel();
    virtual void initialize();
    virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
    virtual void setDatarate();
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
    channelDelay = registerSignal("channelDelay");
    packetLength = par("packetLength");
    timeSlotLength = par("timeSlotLength");
    const char *vstr = par("weibull").stringValue(); // e.g. "1.0227 24.95" which means "scale shape"
    std::vector<double> v = cStringTokenizer(vstr).asDoubleVector();
    shape = v.back();
    v.pop_back();
    scale = v.back();
    v.pop_back();
    setDatarate();
}

void VDrChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t, result);
    setDatarate();
}

void VDrChannel::setDatarate()
{
    //packetLength in Bytes!!
    if(shape == 0)
    {
        cDatarateChannel::setDatarate((packetLength*8)/timeSlotLength);
        emit(channelDelay, timeSlotLength);
    }
    else
    {
            //double nextDatarate = truncnormal(meanDatarate-0.0001,stdDatarate)+0.0001; //in expectancy this will result in meanDr = mean, however, no 0 values will occur
            double delay = timeSlotLength*weibull(scale,shape); //weibull(scale,shape) with mean 1
            cDatarateChannel::setDatarate((packetLength*8)/(delay));
            emit(channelDelay, delay);
        }
}
