#ifndef MESSAGES_H
#define MESSAGES_H

#include "constants.h"
#include "idisplay_controller.h"

#include <cstring>
#include "string_utils.h"

#include <cstdio>

namespace mimi
{

class ICore;

class Message
{
public:
    virtual ~Message() = default;
    virtual Message* clone() const = 0;
};

class InputMessage : public Message
{
protected:
    ICore& core;
public:
    explicit InputMessage(ICore& core) : core(core) {}
    virtual int parse(const char* line, unsigned int argsStartPos) = 0;
    virtual void execute() const = 0;
};

class OutputMessage : public Message
{
public:
    virtual void generate(char* buffer, unsigned long bufferSize) const = 0;
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

    void execute() const override {}

    Message* clone() const override {
        return new HeadlightsMessage(*this);
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

    void execute() const override {}

    Message* clone() const override {
        return new DriveMotorsMessage(*this);
    }
};

class ShowAnimationMessage : public InputMessage
{
public:
    AnimationType animationType = UNDEFINED;

    explicit ShowAnimationMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, const unsigned int argsStartPos) override
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

    void execute() const override {}

    Message* clone() const override {
        return new ShowAnimationMessage(*this);
    }
};

class PrintTextMessage : public InputMessage
{
public:
    char text[language::MAX_ARGUMENT_LENGTH] = "\0";

    explicit PrintTextMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, const unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        bool isString;

        extractLexeme(argsStartPos, lineLen, line, text, isString);
        if (text[0] != '\0' && !isString) return language::PARSE_STATUS_WRONG_ARGUMENT;

        return language::PARSE_STATUS_OK;
    }

    void execute() const override {}

    Message* clone() const override {
        return new PrintTextMessage(*this);
    }
};

class StatusMessage : public OutputMessage
{
    char* name;
    const int controllerId;
    const int textId;
protected:
    explicit StatusMessage(const char* name, const int controllerId, const int textId)
        : OutputMessage(), name(strclone(name)), controllerId(controllerId), textId(textId) {}

    StatusMessage(const StatusMessage& other)
    : name(strclone(other.name)), controllerId(other.controllerId), textId(other.textId) {}

    ~StatusMessage() override {
        free(name);
    }

public:
    void generate(char *buffer, const unsigned long bufferSize) const override
    {
        snprintf(buffer, bufferSize, "%s %d %d", name, controllerId, textId);
    }

    Message* clone() const override
    {
        return new StatusMessage(*this);
    }
};

class InfoMessage final : public StatusMessage
{
public:
    explicit InfoMessage(const int controllerId, const int textId)
        : StatusMessage("info", controllerId, textId) {}
};

class WarnMessage final : public StatusMessage
{
public:
    explicit WarnMessage(const int controllerId, const int textId)
        : StatusMessage("warn", controllerId, textId) {}
};

class ErrorMessage final : public StatusMessage
{
public:
    explicit ErrorMessage(const int controllerId, const int textId)
        : StatusMessage("err", controllerId, textId) {}
};

} // namespace mimi

#endif //MESSAGES_H
