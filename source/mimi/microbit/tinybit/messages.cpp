#include "messages.h"

using namespace mimi::microbit::tinybit;

int PingMessage::parse(const char* line, const unsigned int argsStartPos)
{
    const unsigned int lineLen = strlen(line);
    char argument[language::MAX_ARGUMENT_LENGTH];
    bool isString;
    int status;

    extractLexeme(argsStartPos, lineLen, line, argument, isString);
    time = textToUint<uint64_t>(argument, isString, status);
    if (status < 0) return status;

    return language::PARSE_STATUS_OK;
}

void PingMessage::execute() const
{
    PongMessage pongMessage(time);
    core.getQueueController().getOutputQueue().enqueue(&pongMessage);
}

mimi::Message* PingMessage::clone() const
{
    return new PingMessage(*this);
}
