#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../../ilanguage_controller.h"
#include "messages.h"

#include <stdexcept>

namespace mimi::microbit::tinybit
{

class LanguageController final : public ILanguageController
{
    static constexpr int COMMANDS_COUNT = 4;
    int commandsCounter;
    CommandEntry commandEntries[COMMANDS_COUNT];
public:
    explicit LanguageController(ICore& core)
            : ILanguageController(core, commandEntries, COMMANDS_COUNT)
    {
        int index = 0;
        commandEntries[index++] = {
            "hl",
            [this]() -> Message* { return new HeadlightsMessage(this->core); }
        };
        commandEntries[index++] = {
            "drv",
            [this]() -> Message* { return new DriveMotorsMessage(this->core); }
        };
        commandEntries[index++] = {
            "emo",
            [this]() -> Message* { return new ShowAnimationMessage(this->core); }
        };
        commandEntries[index++] = {
            "prn",
            [this]() -> Message* { return new PrintTextMessage(this->core); }
        };
        commandsCounter = index;
    }

    void init() override
    {
        ILanguageController::init();
        // TODO DZZ Check status!
        if (commandsCounter != COMMANDS_COUNT) // NOLINT(*-branch-clone)
        {
            // TODO DZZ Report status NOT-OK
            return;
        }
        // TODO DZZ Report status OK
    }

    void start() override
    {}

    void stop() override
    {}
};

} // namespace mimi::microbit::tinybit

#endif //COMMAND_PROCESSOR_H
