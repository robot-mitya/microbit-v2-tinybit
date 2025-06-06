#ifndef IHEADLIGHTS_CONTROLLER_H
#define IHEADLIGHTS_CONTROLLER_H

#include <cstdint>
#include "icontroller.h"
#include "constants.h"

namespace mimi
{

class IHeadlightsController : public IController
{
public:
    explicit IHeadlightsController(ICore &core) : IController(core) {}

    int getControllerId() override { return language::CONTROLLER_ID_HEADLIGHTS; }

    virtual void turnOn(uint8_t red, uint8_t green, uint8_t blue) = 0;
    virtual void turnOff() = 0;

    virtual bool isTurnedOn() = 0;
    virtual uint8_t getRed() = 0;
    virtual uint8_t getGreen() = 0;
    virtual uint8_t getBlue() = 0;
};

} // namespace mimi

#endif //IHEADLIGHTS_CONTROLLER_H
