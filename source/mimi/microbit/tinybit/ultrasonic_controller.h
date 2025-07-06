#ifndef ULTRASONIC_CONTROLLER_H
#define ULTRASONIC_CONTROLLER_H

#include "../../icore.h"
#include "MicroBit.h"
#include "ultrasonic_sensor.h"
#include "../../iultrasonic_controller.h"

namespace mimi::microbit::tinybit
{

class UltrasonicController final : public IUltrasonicController {
    volatile bool running = false;
    static UltrasonicController* instance; // NOLINT(*-dynamic-static-initializers)
    static void fiberRunner();

    MicroBit& uBit;

    UltrasonicSensor* sensor = nullptr;
public:
    explicit UltrasonicController(MicroBit& uBit, ICore& core)
        : IUltrasonicController(core), uBit(uBit) {}

    void init() override;
    void start() override;
    void stop() override;
};

} // namespace mimi::microbit::tinybit

#endif //ULTRASONIC_CONTROLLER_H
