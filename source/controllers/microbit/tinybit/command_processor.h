#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../../icommand_processor.h"

namespace mimi::microbit::tinybit
{

    class CommandProcessor final : public ICommandProcessor
    {
    public:
        CommandProcessor();
    };

    // static CommandEntry mnemonicTable[] = {
    //     // {"789", []() -> Message* { return new DummyMessage789(); }},
    // };
    //
    // class CommandProcessor final : public ICommandProcessor
    // {
    // public:
    //     CommandProcessor() : ICommandProcessor(mnemonicTable, sizeof(mnemonicTable) / sizeof(CommandEntry))
    //     {
    //     }
    // };
    //
} // namespace mimi::microbit::tinybit

#endif //COMMAND_PROCESSOR_H
