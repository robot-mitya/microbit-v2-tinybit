#include "icom_controller.h"
#include "icore.h"
#include "ilanguage_controller.h"
#include "string_utils.h"
#include "messages.h"

using namespace mimi;

int IComController::processLine(const char *line) const
{
    const unsigned int len = strlen(line);
    char mnemonic[language::MAX_MNEMONIC_LENGTH + 1];
    bool isString;
    unsigned int pos = 0;
    pos = extractLexeme(pos, len, line, mnemonic, isString);

    InputMessage* message = core.getLanguageController().createMessage(mnemonic);
    if (message == nullptr)
        return language::PARSE_STATUS_UNKNOWN_MNEMONIC;
    int status = message->parse(line, pos);

    if (status == language::PARSE_STATUS_OK)
        core.getQueueController().getInputQueue().enqueue(message);

    return status;
}
