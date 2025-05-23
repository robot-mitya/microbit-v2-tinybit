#ifndef MESSAGES_H
#define MESSAGES_H

#include "constants.h"

#include <cstring>
#include <cerrno>
#include "string_utils.h"

namespace mimi
{
    class ICore;

    class Message
    {
    protected:
        ICore& core;

        static uint8_t textToUint8(const char* text, const bool isString, int& status)
        {
            if (text[0] == '\0')
            {
                status = language::PARSE_STATUS_MISSING_ARGUMENT;
                return 0;
            }
            if (isString)
            {
                status = language::PARSE_STATUS_WRONG_ARGUMENT;
                return 0;
            }
            char *end = nullptr;
            errno = 0;
            const unsigned long value = strtoul(text, &end, 10);
            if (*end == '\0' && value <= 255 && errno == 0)
            {
                status = language::PARSE_STATUS_OK;
                return static_cast<uint8_t>(value);
            }
            status = language::PARSE_STATUS_WRONG_ARGUMENT;
            return 0;
        }
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
            char argument[80];
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

} // namespace mimi

#endif //MESSAGES_H
