#include "ultrasonic_controller.h"

using namespace mimi::microbit::tinybit;

UltrasonicController *UltrasonicController::instance_ = nullptr;

void UltrasonicController::fiberRunner()
{
    if (!instance_) return;
    while (instance_->running_)
    {
        if (instance_->sensor_ && instance_->measuring_)
        {
            const uint64_t currentMillis = system_timer_current_time();
            if (instance_->lastMeasurementMillis_ == 0 ||
                currentMillis - instance_->lastMeasurementMillis_ > instance_->measurementPeriodMillis_)
            {
                instance_->lastMeasurementMillis_ = currentMillis;
                if (instance_->measurementPeriodMillis_ == 0)
                {
                    instance_->measuring_ = false;
                }

                uint32_t distanceInMm = 0;
                const int status = instance_->sensor_->measureAsync(distanceInMm);
                instance_->uBit_.serial.printf("status: %d, distance: %d mm   \r", status, distanceInMm);
            }
        }
        fiber_sleep(10);
    }
}

void UltrasonicController::init()
{
    instance_ = this;
    core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
}

void UltrasonicController::start()
{
    if (running_) return;
    running_ = true;
    measuring_ = false;
    lastMeasurementMillis_ = 0;
    measurementPeriodMillis_ = 0;
    sensor_ = new UltrasonicSensor(uBit_,
        MICROBIT_ID_IO_P16, MICROBIT_PIN_P16,
        MICROBIT_ID_IO_P15, MICROBIT_PIN_P15);
    create_fiber(fiberRunner);
    core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
}

void UltrasonicController::stop()
{
    measuring_ = false;
    running_ = false;
    delete sensor_;
    sensor_ = nullptr;
    core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
}

void UltrasonicController::startMeasuring(const uint32_t periodMillis)
{
    measuring_ = true;
    measurementPeriodMillis_ = periodMillis;
    lastMeasurementMillis_ = 0;
}

void UltrasonicController::stopMeasuring()
{
    measuring_ = false;
}
