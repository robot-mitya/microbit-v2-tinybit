#ifndef MESSAGES_H
#define MESSAGES_H

#include "constants.h"

#include <cstring>
#include "string_utils.h"

#include <cstdio>

namespace mimi
{

class ICore;

class InputMessage
{
protected:
    ICore& core;
public:
    explicit InputMessage(ICore& core) : core(core) {}
    virtual ~InputMessage() = default;
    virtual int parse(const char* line, unsigned int argsStartPos) = 0;
    virtual void execute() const = 0;
};

class OutputMessage
{
protected:
    char text[language::MAX_LINE_LENGTH] = "\0";
public:
    virtual ~OutputMessage() = default;
    const char *getText() const { return text; }
};

class HeadlightsMessage : public InputMessage
{
public:
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    explicit HeadlightsMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[language::MAX_ARGUMENT_LENGTH];
        bool isString;
        int status;

        argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
        if (argument[0] == '\0')
        {
            red = 0;
            green = 0;
            blue = 0;
            return language::PARSE_STATUS_OK;
        }
        red = textToUint8(argument, isString, status);
        if (status < 0) return status;

        argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
        if (argument[0] == '\0')
        {
            green = red;
            blue = red;
            return language::PARSE_STATUS_OK;
        }
        green = textToUint8(argument, isString, status);
        if (status < 0) return status;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        blue = textToUint8(argument, isString, status);
        if (status < 0) return status;

        return language::PARSE_STATUS_OK;
    }
};

class DriveMotorsMessage : public InputMessage
{
public:
    int speedLeft = 0;
    int speedRight = 0;

    explicit DriveMotorsMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[language::MAX_ARGUMENT_LENGTH];
        bool isString;
        int status;

        argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
        if (argument[0] == '\0')
        {
            speedLeft = 0;
            speedRight = 0;
            return language::PARSE_STATUS_OK;
        }
        speedLeft = static_cast<int>(textToLong(argument, isString, -255, 255, status));
        if (status < 0) return status;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        speedRight = argument[0] == '\0'
            ? speedLeft
            : static_cast<int>(textToLong(argument, isString, -255, 255, status));
        if (status < 0) return status;

        return language::PARSE_STATUS_OK;
    }
};

class ShowAnimationMessage : public InputMessage
{
public:
    AnimationType animationType = UNDEFINED;

    explicit ShowAnimationMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[language::MAX_ARGUMENT_LENGTH];
        bool isString;
        int status = 0;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        animationType = argument[0] == '\0'
            ? UNDEFINED
            : static_cast<AnimationType>(textToLong(
                argument, isString, UNDEFINED, ANIMATION_TYPE_COUNT - 1, status));
        if (status < 0) return status;

        return language::PARSE_STATUS_OK;
 }
};

class PrintTextMessage : public InputMessage
{
public:
    char text[language::MAX_ARGUMENT_LENGTH] = "\0";

    explicit PrintTextMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        bool isString;

        extractLexeme(argsStartPos, lineLen, line, text, isString);
        if (text[0] != '\0' && !isString) return language::PARSE_STATUS_WRONG_ARGUMENT;

        return language::PARSE_STATUS_OK;
    }
};

class InfoMessage final : public OutputMessage
{
public:
    explicit InfoMessage(const int controllerId, const int textId) : OutputMessage()
    {
        snprintf(text, sizeof(text), "info %d %d", controllerId, textId);
    }
};

class WarnMessage final : public OutputMessage
{
public:
    explicit WarnMessage(const int controllerId, const int textId) : OutputMessage()
    {
        snprintf(text, sizeof(text), "warn %d %d", controllerId, textId);
    }
};

class ErrorMessage final : public OutputMessage
{
public:
    explicit ErrorMessage(const int controllerId, const int textId) : OutputMessage()
    {
        snprintf(text, sizeof(text), "err %d %d", controllerId, textId);
    }
};

} // namespace mimi

#endif //MESSAGES_H
