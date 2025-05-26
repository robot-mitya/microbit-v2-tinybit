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
    InfoMessage infoMessage(language::CONTROLLER_ID_QUEUE, language::CONTROLLER_INIT_STATUS_OK);
    infoMessage.generate(outputBuffer, language::MAX_LINE_LENGTH);
    core.getQueueController().getOutputQueue().enqueue(&infoMessage);
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
