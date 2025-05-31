#include "queue_controller.h"
#include "CodalFiber.h"
#include "../messages.h"
#include "../constants.h"

using namespace mimi::microbit;

QueueController *QueueController::instance = nullptr;

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
            outputMessage->generate(instance->outputBuffer, language::MAX_LINE_LENGTH);
            instance->core.getUsbComController().sendLine(instance->outputBuffer);
            delete outputMessage;
        }

        codal::fiber_sleep(1);
    }
}

void QueueController::init()
{
    instance = this;
    core.sendInfo(language::CONTROLLER_ID_QUEUE, language::CONTROLLER_INIT_STATUS_OK);
}


void QueueController::start()
{
    if (running) return;
    running = true;
    codal::create_fiber(fiberRunner);
    core.sendInfo(language::CONTROLLER_ID_QUEUE, language::CONTROLLER_START_STATUS_OK);
}

void QueueController::stop()
{
    running = false;
    core.sendInfo(language::CONTROLLER_ID_QUEUE, language::CONTROLLER_STOP_STATUS_OK);
}
