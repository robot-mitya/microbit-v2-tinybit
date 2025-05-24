#ifndef TINYBIT_MESSAGES_H
#define TINYBIT_MESSAGES_H

#include "../../icore.h"
#include "../../messages.h"

namespace mimi::microbit::tinybit
{

    class HeadlightsMessage final : public mimi::HeadlightsMessage
    {
    public:
        explicit HeadlightsMessage(ICore &core) : mimi::HeadlightsMessage(core) {}

        void execute() const override
        {
            core.getHeadlightsController().turnOn(red, green, blue);
        }
    };

    class DriveMotorsMessage final : public DriveMessage
    {
    public:
        explicit DriveMotorsMessage(ICore &core) : mimi::DriveMessage(core) {}

        void execute() const override
        {
            core.getMotorsController().runMotors(speedLeft, speedRight);
        }
    };

    class ShowAnimationMessage final : public mimi::ShowAnimationMessage
    {
    public:
        explicit ShowAnimationMessage(ICore &core) : mimi::ShowAnimationMessage(core) {}

        void execute() const override
        {
            core.getDisplayController().startAnimationAsync(animationType);
        }
    };

    class PrintTextMessage final : public mimi::PrintTextMessage
    {
    public:
        explicit PrintTextMessage(ICore &core) : mimi::PrintTextMessage(core) {}

        void execute() const override
        {
            core.getDisplayController().stopAnimation();
            core.getDisplayController().print(text);
        }
    };

} // namespace mimi

#endif //TINYBIT_MESSAGES_H
