#ifndef CORE_H
#define CORE_H

#include "../../icore.h"
#include "MicroBit.h"
#include "fiber_lock.h"
#include "command_processor.h"
#include "../../queue_controller.h"
#include "headlights_controller.h"
#include "motors_controller.h"
#include "../display_controller.h"

namespace mimi::microbit::tinybit
{

    class Core final : public ICore
    {
        MicroBit uBit;
        FiberLock lock;
        CommandProcessor commandProcessor;
        QueueController queueController;
        HeadlightsController headlightsController;
        MotorsController motorsController;
        DisplayController displayController;
    public:
        Core() : // NOLINT(*-pro-type-member-init, *-use-equals-default)
            // ReSharper disable once CppRedundantMemberInitializer
            lock(),
            commandProcessor(*this),
            queueController(*this, lock),
            headlightsController(uBit, *this),
            motorsController(uBit, *this),
            displayController(uBit, *this) {}

        MicroBit& getMicroBit()
        {
            return uBit;
        }

        ICommandProcessor& getCommandProcessor() override
        {
            return commandProcessor;
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
            ICore::init();
            uBit.init();
            commandProcessor.init();
        }

        void start() override
        {
            ICore::start();
            queueController.start();
        }

        void stop() override
        {
            ICore::stop();
            queueController.stop();
        }

    };

} // namespace mimi

#endif //CORE_H
