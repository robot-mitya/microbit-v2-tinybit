#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdint>
#include "string_utils.h"

#include <cstdlib>
#include <cstring>
#include <cerrno>

constexpr int MESSAGE_PARSE_STATUS_OK = 0;
constexpr int MESSAGE_PARSE_STATUS_MISSING_ARGUMENT = -1;
constexpr int MESSAGE_PARSE_STATUS_WRONG_ARGUMENT = -2;
constexpr int MESSAGE_PARSE_STATUS_TOO_MANY_ARGUMENTS = -3;

class Message
{
protected:
// public:
    static uint8_t textToUint8(const char* text, int& status)
    {
        char *end = nullptr;
        errno = 0;
        const unsigned long value = strtoul(text, &end, 10);
        if (*end == '\0' && value <= 255 && errno == 0)
        {
            status = MESSAGE_PARSE_STATUS_OK;
            return static_cast<uint8_t>(value);
        }
        status = MESSAGE_PARSE_STATUS_WRONG_ARGUMENT;
        return 0;
    }
public:
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

    int parse(const char *line, unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[80];
        int status;

        argsStartPos = extractWord(argsStartPos, lineLen, line, argument);
        if (argument[0] == '\0') return MESSAGE_PARSE_STATUS_MISSING_ARGUMENT;
        red = textToUint8(argument, status);
        if (status < 0) return status;

        argsStartPos = extractWord(argsStartPos, lineLen, line, argument);
        if (argument[0] == '\0') return MESSAGE_PARSE_STATUS_MISSING_ARGUMENT;
        green = textToUint8(argument, status);
        if (status < 0) return status;

        argsStartPos = extractWord(argsStartPos, lineLen, line, argument);
        if (argument[0] == '\0') return MESSAGE_PARSE_STATUS_MISSING_ARGUMENT;
        blue = textToUint8(argument, status);
        if (status < 0) return status;

        extractWord(argsStartPos, lineLen, line, argument);
        if (argument[0] != '\0') return MESSAGE_PARSE_STATUS_TOO_MANY_ARGUMENTS;

        return 0;
    }

    void execute() const override {}
};

#endif //MESSAGES_H
