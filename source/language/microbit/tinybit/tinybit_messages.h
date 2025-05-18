#ifndef TINYBIT_MESSAGES_H
#define TINYBIT_MESSAGES_H

#include "icore.h"
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

} // namespace mimi

#endif //TINYBIT_MESSAGES_H
