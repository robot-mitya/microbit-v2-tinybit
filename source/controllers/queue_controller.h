#ifndef QUEUE_CONTROLLER_H
#define QUEUE_CONTROLLER_H

#include "iqueue_controller.h"
#include "message_queue.h"

namespace mimi
{

class QueueController final : public IQueueController
{
    ILock& lock;
    MessageQueue inputQueue;
    MessageQueue outputQueue;
public:
    explicit QueueController(ICore& core, ILock& lock) // NOLINT(*-pro-type-member-init)
        : IQueueController(core), lock(lock), inputQueue(lock), outputQueue(lock) {}

    void init() override
    {

    }

    void start() override
    {

    }

    void stop() override
    {

    }
};

}

#endif //QUEUE_CONTROLLER_H
