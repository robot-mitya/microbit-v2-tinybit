#ifndef USB_COM_CONTROLLER_H
#define USB_COM_CONTROLLER_H

namespace mimi::microbit
{

class UsbComController : public IComController
{
    MicroBit& uBit;

public:
    explicit UsbComController(MicroBit& uBit, ICore &core) : IComController(core), uBit(uBit) {}

protected:
    void init() override {}
    void start() override {}
    void stop() override {}
};

} // namespace mimi::microbit

#endif //USB_COM_CONTROLLER_H
