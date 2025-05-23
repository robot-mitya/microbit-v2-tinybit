#ifndef QUEUE_CONTROLLER_H
#define QUEUE_CONTROLLER_H

#include "../icore.h"

namespace mimi::microbit
{

class QueueController final : public IQueueController
{
    volatile bool running = false;
    static QueueController* instance; // NOLINT(*-dynamic-static-initializers)
    static void fiberRunner();

public:
    QueueController(ICore &core, ILock &lock) : IQueueController(core, lock) {}
    void init() override;
    void start() override;
    void stop() override;
};

} // namespace mimi::microbit

#endif //QUEUE_CONTROLLER_H
