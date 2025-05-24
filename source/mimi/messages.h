#ifndef MESSAGES_H
#define MESSAGES_H

#include "constants.h"

#include <cstring>
#include "string_utils.h"

namespace mimi
{
    class ICore;

    class Message
    {
    protected:
        ICore& core;
    public:
        explicit Message(ICore& core) : core(core) {}
        virtual ~Message() = default;
        virtual int parse(const char* line, unsigned int argsStartPos) = 0;
        virtual void execute() const = 0;
    };

    class HeadlightsMessage : public Message
    {
    public:
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;

        explicit HeadlightsMessage(ICore &core) : Message(core) {}

        int parse(const char *line, unsigned int argsStartPos) override
        {
            const unsigned int lineLen = strlen(line);
            char argument[language::MAX_ARGUMENT_LENGTH];
            bool isString;
            int status;

            argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
            red = textToUint8(argument, isString, status);
            if (status < 0) return status;

            argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
            green = textToUint8(argument, isString, status);
            if (status < 0) return status;

            argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
            blue = textToUint8(argument, isString, status);
            if (status < 0) return status;

            extractLexeme(argsStartPos, lineLen, line, argument, isString);
            if (argument[0] != '\0') return language::PARSE_STATUS_TOO_MANY_ARGUMENTS;

            return language::PARSE_STATUS_OK;
        }
    };

    class DriveMessage : public Message
    {
    public:
        int speedLeft = 0;
        int speedRight = 0;

        explicit DriveMessage(ICore &core) : Message(core) {}

        int parse(const char *line, unsigned int argsStartPos) override
        {
            const unsigned int lineLen = strlen(line);
            char argument[language::MAX_ARGUMENT_LENGTH];
            bool isString;
            int status;

            argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
            speedLeft = static_cast<int>(textToLong(argument, isString, -255, 255, status));
            if (status < 0) return status;

            argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
            speedRight = static_cast<int>(textToLong(argument, isString, -255, 255, status));
            if (status < 0) return status;

            extractLexeme(argsStartPos, lineLen, line, argument, isString);
            if (argument[0] != '\0') return language::PARSE_STATUS_TOO_MANY_ARGUMENTS;

            return language::PARSE_STATUS_OK;
        }
    };

} // namespace mimi

#endif //MESSAGES_H
