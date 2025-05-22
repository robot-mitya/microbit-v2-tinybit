#include "icom_controller.h"
#include "icore.h"
#include "ilanguage_controller.h"
#include "string_utils.h"
#include "messages.h"

using namespace mimi;

void IComController::processLine(const char *line) const
{
    const unsigned int len = strlen(line);
    char mnemonic[10];
    bool isString;
    unsigned int pos = 0;
    pos = extractLexeme(pos, len, line, mnemonic, isString);

    Message* message = core.getLanguageController().createMessage(mnemonic);
    message->parse(line, pos);
    core.getQueueController().getInputQueue().enqueue(message);
}
