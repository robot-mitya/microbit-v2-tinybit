//
// Created by dmitrydzz on 5/17/25.
//

#ifndef MESSAGE_MOCKS_H
#define MESSAGE_MOCKS_H

#include "../source/mimi/messages.h"

namespace mimi
{

    class HeadlightsMockMessage final : public HeadlightsMessage
    {
    public:
        explicit HeadlightsMockMessage(ICore &core) : HeadlightsMessage(core) {}
        void execute() const override {}
    };

} // namespace mimi

#endif //MESSAGE_MOCKS_H
