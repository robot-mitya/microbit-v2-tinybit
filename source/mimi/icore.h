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

    enum ComChannel {
        USB = 0,
        BLUETOOTH = 1
    };

    class ICore
    {
        static constexpr int CONTROLLERS_COUNT = 7;
        IController* controllers[CONTROLLERS_COUNT] =
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        ComChannel comChannel = BLUETOOTH;
    protected:
        virtual void sendStatus(const char* messageName, int controllerId, int statusId) = 0;
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
            controllers[6] = &getBtComController();

            for (IController* controller : controllers)
                controller->init();
        }

        virtual void start();

        virtual void stop()
        {
            for (IController* controller : controllers)
                controller->stop();
        }

        void sendInfo(int controllerId, int statusId)
        {
            sendStatus("info", controllerId, statusId);
        }

        void sendWarn(int controllerId, int statusId)
        {
            sendStatus("warn", controllerId, statusId);
        }

        void sendError(int controllerId, int statusId)
        {
            sendStatus("err", controllerId, statusId);
        }

        virtual ILanguageController& getLanguageController() = 0;
        virtual IQueueController& getQueueController() = 0;
        virtual IHeadlightsController& getHeadlightsController() = 0;
        virtual IMotorsController& getMotorsController() = 0;
        virtual IDisplayController& getDisplayController() = 0;
        virtual IComController& getUsbComController() = 0;
        virtual IComController& getBtComController() = 0;

        IComController& getCurrentComController()
        {
            return comChannel == BLUETOOTH ? getBtComController() : getUsbComController();
        }
    };

} // namespace mimi

#endif //ICORE_H
