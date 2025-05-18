#ifndef FIBER_LOCK_H
#define FIBER_LOCK_H

#include "CodalFiber.h"
#include "../message_queue.h"

namespace mimi::microbit
{

class FiberLock final : public ILock {
    codal::FiberLock impl;
public:
    FiberLock() : impl(1, codal::FiberLockMode::MUTEX) {}
    void wait() override { impl.wait(); }
    void notify() override { impl.notify(); }
};

} // namespace mimi

#endif //FIBER_LOCK_H
