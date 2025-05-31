#ifndef HEADLIGHTS_CONTROLLER_H
#define HEADLIGHTS_CONTROLLER_H

#include "icore.h"
#include "MicroBit.h"
#include "../../iheadlights_controller.h"
#include "../../constants.h"

namespace mimi::microbit::tinybit
{

class HeadlightsController final : public IHeadlightsController {
    static constexpr uint8_t PWM_ADDRESS = 0x01;
    static constexpr uint8_t RGBs = 0x01;

    MicroBit& uBit;
    MicroBitI2C& i2c;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
public:
    explicit HeadlightsController(MicroBit& uBit, ICore& core)
        : IHeadlightsController(core), uBit(uBit), i2c(uBit.i2c) {}

    void init() override
    {
        core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
    }

    void start() override
    {
        core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
    }

    void stop() override
    {
        core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
    }

    void turnOn(const uint8_t red, const uint8_t green, const uint8_t blue) override
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        uint8_t buf[4] = { RGBs, red, green, blue };
        i2c.write(PWM_ADDRESS << 1, buf, 4);
    }

    void turnOff() override
    {
        turnOn(0, 0, 0);
    }

    bool isTurnedOn() override
    {
        return red != 0 || green != 0 || blue != 0;
    }

    uint8_t getRed() override
    {
        return red;
    }

    uint8_t getGreen() override
    {
        return green;
    }

    uint8_t getBlue() override
    {
        return blue;
    }
};

} // namespace mimi

#endif
