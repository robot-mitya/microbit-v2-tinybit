#ifndef CORE_H
#define CORE_H

#include "fiber_lock.h"
#include "display_controller.h"
#include "tinybit/headlights_controller.h"
#include "../icore.h"
#include "tinybit/motors_controller.h"
#include "../queue_controller.h"

namespace mimi
{

    class Core final : public ICore
    {
        MicroBit uBit;
        FiberLock lock;
        QueueController queueController;
        HeadlightsController headlightsController;
        MotorsController motorsController;
        DisplayController displayController;
    public:
        Core() : // NOLINT(*-pro-type-member-init, *-use-equals-default)
            // ReSharper disable once CppRedundantMemberInitializer
            lock(),
            queueController(*this, lock),
            headlightsController(uBit, *this),
            motorsController(uBit, *this),
            displayController(uBit, *this)
        {}

        MicroBit& getMicroBit() override
        {
            return uBit;
        }

        IQueueController& getQueueController() override
        {
            return queueController;
        }

        IHeadlightsController& getHeadlightsController() override
        {
            return headlightsController;
        }

        IMotorsController& getMotorsController() override
        {
            return motorsController;
        }

        IDisplayController& getDisplayController() override
        {
            return displayController;
        }

        void init() override
        {
            uBit.init();
        }

        void start() override
        {
            queueController.start();
        }

        void stop() override
        {
            queueController.stop();
        }

    };

} // namespace mimi

#endif //CORE_H
