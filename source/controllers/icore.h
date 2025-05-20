#ifndef ICORE_H
#define ICORE_H

#include "icommand_processor.h"
#include "iheadlights_controller.h"
#include "imotors_controller.h"
#include "idisplay_controller.h"
#include "iqueue_controller.h"
#include "iusb_com_controller.h"

namespace mimi
{

    class ICore
    {
        static constexpr int CONTROLLERS_COUNT = 6;
        IController* controllers[CONTROLLERS_COUNT] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    public:
        virtual ~ICore() = default;

        virtual void init()
        {
            controllers[0] = &getCommandProcessor();
            controllers[1] = &getQueueController();
            controllers[2] = &getHeadlightsController();
            controllers[3] = &getMotorsController();
            controllers[4] = &getDisplayController();
            controllers[5] = &getUsbComController();

            for (IController* controller : controllers)
                controller->init();
        }

        virtual void start()
        {
            for (IController* controller : controllers)
                controller->start();
        }

        virtual void stop()
        {
            for (IController* controller : controllers)
                controller->stop();
        }

        virtual ICommandProcessor& getCommandProcessor() = 0;
        virtual IQueueController& getQueueController() = 0;
        virtual IHeadlightsController& getHeadlightsController() = 0;
        virtual IMotorsController& getMotorsController() = 0;
        virtual IDisplayController& getDisplayController() = 0;
        virtual IUsbComController& getUsbComController() = 0;
    };

} // namespace mimi

#endif //ICORE_H
