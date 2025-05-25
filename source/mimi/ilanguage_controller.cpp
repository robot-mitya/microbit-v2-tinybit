#include "ilanguage_controller.h"
#include "messages.h"

using namespace mimi;

/**
 * 1. Extracts mnemonic.
 * 2. Performs a binary search and creates a Message object
 *    based on the provided mnemonic. Returns nullptr if not found.
 * 3. Parses the message and returns it.
 */
InputMessage* ILanguageController::createMessage(const char* line, int& status) const {
    const unsigned int len = strlen(line);
    char mnemonic[language::MAX_MNEMONIC_LENGTH + 1];
    bool isString;
    unsigned int pos = 0;
    pos = extractLexeme(pos, len, line, mnemonic, isString);

    InputMessage* result = nullptr;
    int left = 0, right = commandCount - 1;
    while (initialized && left <= right) {
        const int mid = (left + right) / 2;
        const int cmp = strcmp(mnemonic, commandTable[mid].mnemonic);
        if (cmp == 0)
        {
            result = commandTable[mid].createFunc();
            break;
        }
        if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    status = result == nullptr
        ? language::PARSE_STATUS_UNKNOWN_MNEMONIC
        : result->parse(line, pos);

    if (status == language::PARSE_STATUS_OK) return result;
    return nullptr;
}
