#ifndef TINYBIT_MESSAGES_H
#define TINYBIT_MESSAGES_H

#include "../../messages.h"

namespace mimi::microbit::tinybit
{

    class HeadlightsTinybitMessage final : public HeadlightsMessage
    {
    public:
        void execute() const override
        {
            //...
        }
    };

} // namespace mimi

#endif //TINYBIT_MESSAGES_H
