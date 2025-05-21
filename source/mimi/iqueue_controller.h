#ifndef IQUEUE_CONTROLLER_H
#define IQUEUE_CONTROLLER_H

#include "icontroller.h"

namespace mimi
{

class IQueueController : public IController
{
public:
    explicit IQueueController(ICore &core) : IController(core) {}

    // virtual void start() = 0;
    // virtual void stop() = 0;
};

} // namespace mimi

#endif //IQUEUE_CONTROLLER_H
