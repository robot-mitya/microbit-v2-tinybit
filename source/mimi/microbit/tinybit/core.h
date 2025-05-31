#ifndef CORE_H
#define CORE_H

#include "../../icore.h"
#include "../../../codal-microbit-v2/model/MicroBit.h"
#include "../fiber_lock.h"
#include "language_controller.h"
#include "headlights_controller.h"
#include "motors_controller.h"
#include "../queue_controller.h"
#include "../display_controller.h"
#include "../usb_com_controller.h"

namespace mimi::microbit::tinybit
{

    class Core final : public ICore
    {
        MicroBit uBit;
        FiberLock lock;
        LanguageController languageController;
        QueueController queueController;
        HeadlightsController headlightsController;
        MotorsController motorsController;
        DisplayController displayController;
        UsbComController usbComController;
    protected:
        void sendStatus(const char* messageName, int controllerId, int statusId) override;
    public:
        Core() : // NOLINT(*-pro-type-member-init, *-use-equals-default)
            // ReSharper disable once CppRedundantMemberInitializer
            lock(),
            languageController(*this),
            queueController(*this, lock),
            headlightsController(uBit, *this),
            motorsController(uBit, *this),
            displayController(uBit, *this),
            usbComController(uBit, *this) {}

        MicroBit& getMicroBit()
        {
            return uBit;
        }

        ILanguageController& getLanguageController() override
        {
            return languageController;
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

        IComController& getUsbComController() override
        {
            return usbComController;
        }

        void init() override
        {
            uBit.init();
            ICore::init();
        }

    };

} // namespace mimi

#endif //CORE_H
