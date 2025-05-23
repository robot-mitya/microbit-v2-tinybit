#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../../ilanguage_controller.h"
#include "messages.h"

namespace mimi::microbit::tinybit
{

class LanguageController final : public ILanguageController
{
    static constexpr int COMMANDS_COUNT = 1;
    CommandEntry commandEntries[COMMANDS_COUNT];
public:
    explicit LanguageController(ICore& core)
            : ILanguageController(core, commandEntries, COMMANDS_COUNT)
    {
        commandEntries[0] = {
            "HL",
            [this]() -> Message* { return new HeadlightsMessage(this->core); }
        };
    }

    void init() override
    {
        ILanguageController::init();
    }

    void start() override
    {}

    void stop() override
    {}
};

} // namespace mimi::microbit::tinybit

#endif //COMMAND_PROCESSOR_H
