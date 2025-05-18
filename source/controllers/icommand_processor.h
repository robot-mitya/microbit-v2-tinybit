// ReSharper disable CppUseAuto
#ifndef ICOMMAND_PROCESSOR_H
#define ICOMMAND_PROCESSOR_H

#include <cstring>

namespace mimi
{

class Message;

struct CommandEntry {
    const char* mnemonic;
    Message* (*createFunc)();
};

class ICommandProcessor {
protected:
    CommandEntry* commandTable;
    int commandCount;
    bool initialized = false;

    static int compareEntries(const void* a, const void* b) {
        const CommandEntry* ea = static_cast<const CommandEntry*>(a);
        const CommandEntry* eb = static_cast<const CommandEntry*>(b);
        return strcmp(ea->mnemonic, eb->mnemonic);
    }

    ICommandProcessor(CommandEntry* table, const int count)
        : commandTable(table), commandCount(count) {}

public:
    /**
     * Call this before using createMessage().
     * Sorts the command table lexicographically by mnemonic.
     */
    void init() {
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
