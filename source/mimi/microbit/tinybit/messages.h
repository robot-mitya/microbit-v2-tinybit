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

    class DriveMotorsMessage final : public mimi::DriveMessage
    {
    public:
        explicit DriveMotorsMessage(ICore &core) : mimi::DriveMessage(core) {}

        void execute() const override
        {
            core.getMotorsController().runMotors(speedLeft, speedRight);
        }
    };

} // namespace mimi

#endif //TINYBIT_MESSAGES_H
