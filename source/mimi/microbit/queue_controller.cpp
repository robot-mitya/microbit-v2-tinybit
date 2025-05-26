#include "queue_controller.h"
#include "CodalFiber.h"
#include "Tests.h"
#include "../messages.h"
#include "../constants.h"

using namespace mimi::microbit;

QueueController *QueueController::instance = nullptr;

static char outputBuffer[mimi::language::MAX_LINE_LENGTH + 1];

void QueueController::fiberRunner()
{
    if (!instance) return;
    while (instance->running)
    {
        const InputMessage* inputMessage = instance->inputQueue.dequeue();
        if (inputMessage != nullptr)
        {
            inputMessage->execute();
            delete inputMessage;
        }

        const OutputMessage* outputMessage = instance->outputQueue.dequeue();
        if (outputMessage != nullptr)
        {
            outputMessage->generate(outputBuffer, mimi::language::MAX_LINE_LENGTH);
            instance->core.getUsbComController().sendLine(outputBuffer);
            delete outputMessage;
        }

        fiber_sleep(1);
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
    create_fiber(fiberRunner);
}

void QueueController::stop()
{
    running = false;
}
