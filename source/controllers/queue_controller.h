#ifndef QUEUE_CONTROLLER_H
#define QUEUE_CONTROLLER_H

#include "iqueue_controller.h"
#include "message_queue.h"

namespace mimi
{

    class ICore;

    class QueueController final : public IQueueController
    {
        ICore& core;
        ILock& lock;
        MessageQueue inputQueue;
        MessageQueue outputQueue;
    public:
        explicit QueueController(ICore& core, ILock& lock)
            : core(core), lock(lock), inputQueue(lock), outputQueue(lock) {}

        void start() override
        {

        }

        void stop() override
        {

        }
    };

}

#endif //QUEUE_CONTROLLER_H
