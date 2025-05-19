#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "icore.h"
#include "../../icommand_processor.h"
#include "../language/microbit/tinybit/tinybit_messages.h"

namespace mimi::microbit::tinybit
{

class CommandProcessor final : public ICommandProcessor
{
    static constexpr int COMMANDS_COUNT = 1;
    ICore& core;
    CommandEntry commandEntries[COMMANDS_COUNT];
public:
    explicit CommandProcessor(ICore& core)
            : ICommandProcessor(commandEntries, COMMANDS_COUNT), core(core)
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
