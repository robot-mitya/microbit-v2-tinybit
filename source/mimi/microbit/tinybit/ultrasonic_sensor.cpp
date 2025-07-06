#include "ultrasonic_sensor.h"

#include "CodalFiber.h"
#include "codal-core/inc/driver-models/Timer.h"
#include "../../constants.h"

extern Timer system_timer;

using namespace mimi::microbit::tinybit;

int UltrasonicSensor::measureAsync(uint32_t& distanceInMillimeters)
{
    constexpr uint64_t TIMEOUT_US = 100000;
    distanceInMillimeters = 0;

    trig.setDigitalValue(0);
    fiber_sleep(2);

    trig.setDigitalValue(1);
    system_timer_wait_us(10);
    trig.setDigitalValue(0);

    const uint64_t waitStart = system_timer_current_time_us();
    while (echo.getDigitalValue() == 0)
    {
        if (system_timer_current_time_us() - waitStart > TIMEOUT_US)
            return controller::SENSOR_TIMEOUT;
        system_timer_wait_us(10);
    }

    const uint64_t start = system_timer_current_time_us();

    while (echo.getDigitalValue() == 1)
    {
        if (system_timer_current_time_us() - start > TIMEOUT_US)
            return controller::SENSOR_TIMEOUT;
        system_timer_wait_us(10);
    }

    const uint64_t end = system_timer_current_time_us();
    const uint64_t duration = end - start;

    distanceInMillimeters = duration * 100 / 583;
    return controller::OPERATION_STATUS_OK;
}