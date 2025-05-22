#ifndef ICORE_H
#define ICORE_H

#include "ilanguage_controller.h"
#include "iheadlights_controller.h"
#include "imotors_controller.h"
#include "idisplay_controller.h"
#include "iqueue_controller.h"
#include "icom_controller.h"

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
            controllers[0] = &getLanguageController();
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

        virtual ILanguageController& getLanguageController() = 0;
        virtual IQueueController& getQueueController() = 0;
        virtual IHeadlightsController& getHeadlightsController() = 0;
        virtual IMotorsController& getMotorsController() = 0;
        virtual IDisplayController& getDisplayController() = 0;
        virtual IComController& getUsbComController() = 0;
    };

} // namespace mimi

#endif //ICORE_H
