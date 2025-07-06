#include "ultrasonic_controller.h"

using namespace mimi::microbit::tinybit;

UltrasonicController *UltrasonicController::instance = nullptr;

void UltrasonicController::fiberRunner()
{
    if (!instance) return;
    while (instance->running)
    {
        if (instance->sensor)
        {
            uint32_t distanceInMm = 0;
            const int status = instance->sensor->measureAsync(distanceInMm);
            instance->uBit.serial.printf("status: %d, distance: %d mm   \r", status, distanceInMm);
        }
        fiber_sleep(5000);
    }
}

void UltrasonicController::init()
{
    instance = this;
    core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
}

void UltrasonicController::start()
{
    if (running) return;
    running = true;
    sensor = new UltrasonicSensor(uBit,
        MICROBIT_ID_IO_P16, MICROBIT_PIN_P16,
        MICROBIT_ID_IO_P15, MICROBIT_PIN_P15);
    create_fiber(fiberRunner);
    core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
}

void UltrasonicController::stop()
{
    running = false;
    delete sensor;
    sensor = nullptr;
    core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
}
