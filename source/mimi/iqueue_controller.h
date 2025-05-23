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
    MessageQueue inputQueue;
    MessageQueue outputQueue;
public:
    explicit IQueueController(ICore& core, ILock& lock) // NOLINT(*-pro-type-member-init)
        : IController(core), lock(lock), inputQueue(lock), outputQueue(lock) {}

    MessageQueue& getInputQueue() { return inputQueue; }
    MessageQueue& getOutputQueue() { return outputQueue; }
};

} // namespace mimi

#endif //IQUEUE_CONTROLLER_H
