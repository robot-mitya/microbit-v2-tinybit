#ifndef ICORE_H
#define ICORE_H

#include <functional>

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
public:
    enum class ComChannel { USB, BLUETOOTH };
    using SignalCallback = std::function<void(int controllerId, int signal)>;
private:
    static constexpr int CONTROLLERS_COUNT = 7;
    IController* controllers_[CONTROLLERS_COUNT] =
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    ComChannel comChannel_ = ComChannel::BLUETOOTH;
    SignalCallback signalCallback_ = nullptr;
protected:
    virtual void sendStatus(const char* messageName, int controllerId, int statusId) = 0;
public:
    virtual ~ICore() = default;

    ComChannel getComChannel() const { return comChannel_; }
    void setComChannel(const ComChannel comChannel) { comChannel_ = comChannel; }

    SignalCallback getSignalCallback() const { return signalCallback_; }
    void setSignalCallback(const SignalCallback &signalCallback) { signalCallback_ = std::move(signalCallback); }

    virtual void init()
    {
        controllers_[0] = &getLanguageController();
        controllers_[1] = &getQueueController();
        controllers_[2] = &getHeadlightsController();
        controllers_[3] = &getMotorsController();
        controllers_[4] = &getDisplayController();
        controllers_[5] = &getUsbComController();
        controllers_[6] = &getBtComController();

        for (IController* controller : controllers_)
            controller->init();
    }

    virtual void start();

    virtual void stop()
    {
        for (IController* controller : controllers_)
            controller->stop();
    }

    void sendInfo(const int controllerId, const int statusId)
    {
        sendStatus("info", controllerId, statusId);
    }

    void sendWarn(const int controllerId, const int statusId)
    {
        sendStatus("warn", controllerId, statusId);
    }

    void sendError(const int controllerId, const int statusId)
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
        return comChannel_ == ComChannel::BLUETOOTH ? getBtComController() : getUsbComController();
    }
};

} // namespace mimi

#endif //ICORE_H
