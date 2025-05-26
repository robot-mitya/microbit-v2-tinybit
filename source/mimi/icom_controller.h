#ifndef ICOM_CONTROLLER_H
#define ICOM_CONTROLLER_H

#include "icontroller.h"
#include "ilanguage_controller.h"

namespace mimi
{

class IComController : public IController
{
protected:
    int processLine(const char *line) const;
public:
    explicit IComController(ICore &core) : IController(core) {}
    virtual void sendLine(const char *line) = 0;
};

} // namespace mimi

#endif //ICOM_CONTROLLER_H
