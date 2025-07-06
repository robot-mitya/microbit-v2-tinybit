#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "../../icore.h"
#include "codal-microbit-v2/model/MicroBit.h"

namespace mimi::microbit::tinybit
{

class UltrasonicSensor final
{
    MicroBit& uBit;
    MicroBitPin trig;
    MicroBitPin echo;
public:
    explicit UltrasonicSensor(MicroBit& uBit, const int trig_pin_id, const PinNumber trig_pin_name,
        const int echo_pin_id, const PinNumber echo_pin_name) :
        uBit(uBit),
        trig(trig_pin_id, trig_pin_name, PIN_CAPABILITY_DIGITAL),
        echo(echo_pin_id, echo_pin_name, PIN_CAPABILITY_DIGITAL) {}

    ~UltrasonicSensor()
    {
        trig.setDigitalValue(0);
        trig.setPull(PullMode::None);
        echo.setDigitalValue(0);
        echo.setPull(PullMode::None);
    }

    int measureAsync(uint32_t& distanceInMillimeters);
};


} // namespace mimi::microbit::tinybit

#endif //ULTRASONIC_SENSOR_H
