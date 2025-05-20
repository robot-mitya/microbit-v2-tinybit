#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../../icommand_processor.h"
#include "../language/microbit/tinybit/tinybit_messages.h"

namespace mimi::microbit::tinybit
{

class CommandProcessor final : public ICommandProcessor
{
    static constexpr int COMMANDS_COUNT = 1;
    CommandEntry commandEntries[COMMANDS_COUNT];
public:
    explicit CommandProcessor(ICore& core)
            : ICommandProcessor(core, commandEntries, COMMANDS_COUNT)
    {
        commandEntries[0] = {
            "HL",
            [this]() -> Message* { return new HeadlightsMessage(this->core); }
        };
    }

    void init() override
    {}

    void start() override
    {}

    void stop() override
    {}
};

} // namespace mimi::microbit::tinybit

#endif //COMMAND_PROCESSOR_H
