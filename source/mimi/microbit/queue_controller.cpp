#include "queue_controller.h"
#include "CodalFiber.h"
#include "../messages.h""

using namespace mimi::microbit;

QueueController *QueueController::instance = nullptr;

void QueueController::fiberRunner()
{
    if (!instance) return;
    while (instance->running)
    {
        InputMessage* inputMessage = instance->inputQueue.dequeue();
        if (inputMessage != nullptr)
            inputMessage->execute();

        codal::fiber_sleep(1);
    }
}

void QueueController::init()
{
    instance = this;
}


void QueueController::start()
{
    if (running) return;
    running = true;
    codal::create_fiber(fiberRunner);
}

void QueueController::stop()
{
    running = false;
}
