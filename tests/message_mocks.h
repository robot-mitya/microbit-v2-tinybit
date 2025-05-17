//
// Created by dmitrydzz on 5/17/25.
//

#ifndef MESSAGE_MOCKS_H
#define MESSAGE_MOCKS_H

#include "../source/language/messages.h"

namespace mimi
{

    class HeadlightsMockMessage final : public HeadlightsMessage
    {
    public:
        void execute() const override {}
    };

} // namespace mimi

#endif //MESSAGE_MOCKS_H
