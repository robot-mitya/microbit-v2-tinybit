//
// Created by dmitrydzz on 5/17/25.
//

#ifndef MESSAGE_MOCKS_H
#define MESSAGE_MOCKS_H

#include "../source/mimi/messages.h"
#include "../source/mimi/microbit/tinybit/messages.h"

namespace mimi::tests::messages
{

    class HeadlightsMockMessage final : public HeadlightsMessage
    {
    public:
        explicit HeadlightsMockMessage(ICore &core) : HeadlightsMessage(core) {}
        void execute() const override {}
    };

    class DriveMotorsMockMessage final : public DriveMotorsMessage
    {
    public:
        explicit DriveMotorsMockMessage(ICore &core) : DriveMotorsMessage(core) {}
        void execute() const override {}
    };

} // namespace mimi::tests::messages

#endif //MESSAGE_MOCKS_H
