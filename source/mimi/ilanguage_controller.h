// ReSharper disable CppUseAuto
#ifndef ICOMMAND_PROCESSOR_H
#define ICOMMAND_PROCESSOR_H

#include <cstring>
#include "icontroller.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "messages.h"
#include "string_utils.h"

#include <cstdlib>
#include <functional>

namespace mimi
{

class InputMessage;

struct CommandEntry { // NOLINT(*-pro-type-member-init)
    const char* mnemonic;
    std::function<InputMessage *()> createFunc;
};

class ILanguageController : public IController {
protected:
    CommandEntry* commandTable;
    int commandCount;
    bool initialized = false;

    static int compareEntries(const void* a, const void* b) {
        const auto* ea = static_cast<const CommandEntry*>(a);
        const auto* eb = static_cast<const CommandEntry*>(b);
        return strcmp(ea->mnemonic, eb->mnemonic);
    }

    explicit ILanguageController(ICore &core, CommandEntry *table, const int count)
        : IController(core), commandTable(table), commandCount(count)
    {
    }

public:
    /**
     * Call this before using createMessage().
     * Sorts the command table lexicographically by mnemonic.
     */
    void init() override {
        if (!initialized) {
            qsort(commandTable, commandCount, sizeof(CommandEntry), compareEntries);
            initialized = true;
        }
    }

    /**
     * 1. Extracts mnemonic.
     * 2. Performs a binary search and creates a Message object
     *    based on the provided mnemonic. Returns nullptr if not found.
     * 3. Parses the message and returns it.
     */
    InputMessage* createMessage(const char* line, int& status) const;
};

} // namespace mimi

#endif // ICOMMAND_PROCESSOR_H
