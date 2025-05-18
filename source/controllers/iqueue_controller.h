#ifndef IQUEUE_CONTROLLER_H
#define IQUEUE_CONTROLLER_H

namespace mimi
{

class ICore;

class IQueueController
{
public:
    virtual ~IQueueController() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace mimi

#endif //IQUEUE_CONTROLLER_H
