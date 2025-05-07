#ifndef HEADLIGHTS_CONTROLLER_H
#define HEADLIGHTS_CONTROLLER_H

#include "MicroBit.h"

class HeadlightsController {
private:
    static const uint8_t PWM_ADDRESS = 0x01;
    static const uint8_t RGBs = 0x01;

    MicroBit& uBit;
    MicroBitI2C& i2c;

public:
    HeadlightsController(MicroBit& uBit)
        : uBit(uBit), i2c(uBit.i2c) {}

    void turnOn(uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t buf[4] = { RGBs, red, green, blue };
        i2c.write(PWM_ADDRESS << 1, (uint8_t*)buf, 4);
    }

    void turnOff() {
        turnOn(0, 0, 0);
    }
};

#endif
