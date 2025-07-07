#ifndef IULTRASONIC_CONTROLLER_H
#define IULTRASONIC_CONTROLLER_H

#include <cstdint>
#include "icontroller.h"
#include "constants.h"

namespace mimi
{

class IUltrasonicController : public IController
{
public:
    explicit IUltrasonicController(ICore &core) : IController(core) {}

    int getControllerId() override { return language::CONTROLLER_ID_ULTRASONIC; }

    virtual void startMeasuring(uint32_t periodMillis) = 0; // (zero for single measurement)
    virtual void stopMeasuring() = 0;
};

} // namespace mimi

#endif //IULTRASONIC_CONTROLLER_H
