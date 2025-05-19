#ifndef IMOTORS_CONTROLLER_H
#define IMOTORS_CONTROLLER_H

#include "icontroller.h"

namespace mimi
{

class IMotorsController : public IController
{
public:
    // virtual ~IMotorsController() = default;

    virtual void runMotors(int speedLeft, int speedRight) = 0;
    virtual void stopMotors() = 0;
};

} // namespace mimi

#endif //IMOTORS_CONTROLLER_H
