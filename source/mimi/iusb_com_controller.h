#ifndef IUSB_COM_CONTROLLER_H
#define IUSB_COM_CONTROLLER_H

#include "icontroller.h"

namespace mimi
{

class IUsbComController : public IController
{
protected:
    virtual void processLine(const char *line) const = 0;
public:
    explicit IUsbComController(ICore &core) : IController(core) {}
};

} // namespace mimi

#endif //IUSB_COM_CONTROLLER_H
