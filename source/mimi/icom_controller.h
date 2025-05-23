#ifndef ICOM_CONTROLLER_H
#define ICOM_CONTROLLER_H

#include "icontroller.h"
#include "ilanguage_controller.h"
#include "string_utils.h"

namespace mimi
{

class IComController : public IController
{
protected:
    int processLine(const char *line) const;
    virtual void reportStatus(int status) const = 0;
public:
    explicit IComController(ICore &core) : IController(core) {}
};

} // namespace mimi

#endif //ICOM_CONTROLLER_H
