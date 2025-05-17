#ifndef CORE_H
#define CORE_H

#include "display_controller.h"
#include "headlights_controller.h"
#include "icore.h"
#include "motors_controller.h"

namespace mimi
{

    class Core final : public ICore
    {
        MicroBit uBit;
        HeadlightsController headlightsController;
        MotorsController motorsController;
        DisplayController displayController;
    public:
        Core() : // NOLINT(*-pro-type-member-init, *-use-equals-default)
            headlightsController(uBit, *this),
            motorsController(uBit, *this),
            displayController(uBit, *this)
        {}

        MicroBit& getMicroBit() override
        {
            return uBit;
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
        }

        void stop() override
        {
        }

    };

} // namespace mimi

#endif //CORE_H
