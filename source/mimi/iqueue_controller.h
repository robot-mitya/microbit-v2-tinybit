#ifndef IQUEUE_CONTROLLER_H
#define IQUEUE_CONTROLLER_H

#include "icontroller.h"
#include "message_queue.h"

namespace mimi
{

class IQueueController : public IController
{
protected:
    ILock& lock;
    MessageQueue<InputMessage> inputQueue;
    MessageQueue<OutputMessage> outputQueue;
public:
    explicit IQueueController(ICore& core, ILock& lock) // NOLINT(*-pro-type-member-init)
        : IController(core), lock(lock), inputQueue(lock), outputQueue(lock) {}

    MessageQueue<InputMessage>& getInputQueue() { return inputQueue; }
    MessageQueue<OutputMessage>& getOutputQueue() { return outputQueue; }
};

} // namespace mimi

#endif //IQUEUE_CONTROLLER_H
