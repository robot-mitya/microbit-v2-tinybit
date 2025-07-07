#ifndef ULTRASONIC_CONTROLLER_H
#define ULTRASONIC_CONTROLLER_H

#include "../../icore.h"
#include "MicroBit.h"
#include "ultrasonic_sensor.h"
#include "../../iultrasonic_controller.h"

namespace mimi::microbit::tinybit
{

class UltrasonicController final : public IUltrasonicController {
    volatile bool running_ = false;
    static UltrasonicController* instance_; // NOLINT(*-dynamic-static-initializers)
    static void fiberRunner();

    MicroBit& uBit_;

    UltrasonicSensor* sensor_ = nullptr;
    bool measuring_ = false;
    uint64_t measurementPeriodMillis_ = 0;
    uint64_t lastMeasurementMillis_ = 0;
public:
    explicit UltrasonicController(MicroBit& uBit, ICore& core)
        : IUltrasonicController(core), uBit_(uBit) {}

    void init() override;
    void start() override;
    void stop() override;

    void startMeasuring(uint32_t periodMillis) override; // (zero for single measurement)
    void stopMeasuring() override;
};

} // namespace mimi::microbit::tinybit

#endif //ULTRASONIC_CONTROLLER_H
