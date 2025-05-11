#ifndef HEADLIGHTS_CONTROLLER_H
#define HEADLIGHTS_CONTROLLER_H

#include "MicroBit.h"
#include "iheadlights_controller.h"

class ICore;

class HeadlightsController : public IHeadlightsController {
    static constexpr uint8_t PWM_ADDRESS = 0x01;
    static constexpr uint8_t RGBs = 0x01;

    MicroBit& uBit;
    MicroBitI2C& i2c;
    ICore& core;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
public:
    explicit HeadlightsController(MicroBit& uBit, ICore& core)
        : uBit(uBit), i2c(uBit.i2c),  core(core) {}

    void turnOn(uint8_t red, uint8_t green, uint8_t blue) override
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

#endif
