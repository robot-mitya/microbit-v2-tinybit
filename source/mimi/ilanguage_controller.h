// ReSharper disable CppUseAuto
#ifndef ICOMMAND_PROCESSOR_H
#define ICOMMAND_PROCESSOR_H

#include <cstring>
#include "icontroller.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdlib>
#include <functional>

namespace mimi
{

class Message;

struct CommandEntry { // NOLINT(*-pro-type-member-init)
    const char* mnemonic;
    std::function<Message *()> createFunc;
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
     * Performs a binary search and creates a Message object
     * based on the provided mnemonic. Returns nullptr if not found.
     */
    Message* createMessage(const char* mnemonic) const {
        int left = 0, right = commandCount - 1;
        while (initialized && left <= right) {
            const int mid = (left + right) / 2;
            const int cmp = strcmp(mnemonic, commandTable[mid].mnemonic);
            if (cmp == 0)
                return commandTable[mid].createFunc();
            if (cmp < 0)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return nullptr;
    }
};

} // namespace mimi

#endif // ICOMMAND_PROCESSOR_H
