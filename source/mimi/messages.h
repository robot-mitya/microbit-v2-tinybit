#ifndef MESSAGES_H
#define MESSAGES_H

#include "constants.h"
#include "idisplay_controller.h"

#include <cstring>
#include <cinttypes>
// #include "string_utils.h"

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

class PingMessage : public InputMessage
{
public:
    explicit PingMessage(ICore &core) : InputMessage(core) {}
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
        red = textToUint<uint8_t>(argument, isString, status);
        if (status < 0) return status;

        argsStartPos = extractLexeme(argsStartPos, lineLen, line, argument, isString);
        if (argument[0] == '\0')
        {
            green = red;
            blue = red;
            return language::PARSE_STATUS_OK;
        }
        green = textToUint<uint8_t>(argument, isString, status);
        if (status < 0) return status;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        blue = textToUint<uint8_t>(argument, isString, status);
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
        speedLeft = static_cast<int>(textToLimitedInt<int16_t>(argument, isString, -255, 255, status));
        if (status < 0) return status;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        speedRight = argument[0] == '\0'
            ? speedLeft
            : static_cast<int>(textToLimitedInt<int16_t>(argument, isString, -255, 255, status));
        if (status < 0) return status;

        return language::PARSE_STATUS_OK;
    }

    void execute() const override {}

    Message* clone() const override {
        return new DriveMotorsMessage(*this);
    }
};

class DistanceRequestMessage : public InputMessage
{
public:
    uint32_t periodMillis = 0;

    explicit DistanceRequestMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, const unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[language::MAX_ARGUMENT_LENGTH];
        bool isString;
        int status;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        if (argument[0] == '\0')
        {
            periodMillis = 0;
            return language::PARSE_STATUS_OK;
        }
        periodMillis = textToUint<uint32_t>(argument, isString, status);
        if (status < 0) return status;

        return language::PARSE_STATUS_OK;
    }

    void execute() const override {}

    Message* clone() const override {
        return new DistanceRequestMessage(*this);
    }
};

class ShowAnimationMessage : public InputMessage
{
public:
    AnimationType animationType = AnimationType::UNDEFINED;

    explicit ShowAnimationMessage(ICore &core) : InputMessage(core) {}

    int parse(const char *line, const unsigned int argsStartPos) override
    {
        const unsigned int lineLen = strlen(line);
        char argument[language::MAX_ARGUMENT_LENGTH];
        bool isString;
        int status = 0;

        extractLexeme(argsStartPos, lineLen, line, argument, isString);
        animationType = argument[0] == '\0'
            ? AnimationType::UNDEFINED
            : static_cast<AnimationType>(textToLimitedInt<uint8_t>(
                argument,
                isString,
                static_cast<uint8_t>(AnimationType::UNDEFINED),
                static_cast<uint8_t>(AnimationType::ANIMATION_TYPE_COUNT) - 1,
                status));
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
    char text[language::MAX_ARGUMENT_LENGTH + 1] = "\0";

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

class PongMessage final : public OutputMessage
{
    const uint64_t time;
public:
    explicit PongMessage(const uint64_t time) : OutputMessage(), time(time) {}

    PongMessage(const PongMessage& other)
        : time(other.time) {}

    void generate(char *buffer, const unsigned long bufferSize) const override
    {
        char numBuf[21]; // 20 digits + \0
        utoa64(time, numBuf);
        snprintf(buffer, bufferSize, "pong %s\r\n", numBuf);
    }

    Message* clone() const override
    {
        return new PongMessage(*this);
    }
};

class StatusMessage final : public OutputMessage
{
    char* name;
    const int controllerId;
    const int textId;
public:
    explicit StatusMessage(const char* name, int controllerId, int textId);

    StatusMessage(const StatusMessage& other);

    ~StatusMessage() override;

    void generate(char *buffer, const unsigned long bufferSize) const override
    {
        snprintf(buffer, bufferSize, "%s %d %d\r\n", name, controllerId, textId);
    }

    Message* clone() const override
    {
        return new StatusMessage(*this);
    }
};

class DistanceResponseMessage final : public OutputMessage
{
    char* name;
    const uint32_t distanceInMillimeters;
public:
    explicit DistanceResponseMessage(uint32_t distanceInMillimeters);

    DistanceResponseMessage(const DistanceResponseMessage& other);

    ~DistanceResponseMessage() override;

    void generate(char *buffer, const unsigned long bufferSize) const override
    {
        snprintf(buffer, bufferSize, "%s %ld\r\n", name, distanceInMillimeters);
    }

    Message* clone() const override
    {
        return new DistanceResponseMessage(*this);
    }
};

} // namespace mimi

#endif //MESSAGES_H
