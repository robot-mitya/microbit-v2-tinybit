#ifndef IMOTORS_CONTROLLER_H
#define IMOTORS_CONTROLLER_H

#include "icontroller.h"
#include "constants.h"

namespace mimi
{

class IMotorsController : public IController
{
public:
    explicit IMotorsController(ICore &core) : IController(core) {}
    virtual void runMotors(int speedLeft, int speedRight) = 0;
    virtual void stopMotors() = 0;
    int getControllerId() override { return language::CONTROLLER_ID_MOTORS; }
};

} // namespace mimi

#endif //IMOTORS_CONTROLLER_H
