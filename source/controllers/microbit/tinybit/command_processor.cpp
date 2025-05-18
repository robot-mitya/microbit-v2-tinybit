#include "command_processor.h"
#include "../../icommand_processor.h"
#include "../../../language/microbit/tinybit/tinybit_messages.h"

using namespace mimi;
using namespace mimi::microbit::tinybit;

static CommandEntry mnemonicTable[] = {
    {"HL", []() -> Message* { return new microbit::tinybit::HeadlightsMessage(); }},
};

CommandProcessor::CommandProcessor()
    : ICommandProcessor(mnemonicTable, sizeof(mnemonicTable) / sizeof(CommandEntry)) {}
