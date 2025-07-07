#ifndef TINYBIT_MESSAGES_H
#define TINYBIT_MESSAGES_H

#include "../../icore.h"
#include "../../messages.h"

namespace mimi::microbit::tinybit
{

class PingMessage final : public mimi::PingMessage
{
public:
    uint64_t time = 0;
    explicit PingMessage(ICore& core) : mimi::PingMessage(core) {}
    int parse(const char* line, unsigned int argsStartPos) override;
    void execute() const override;
    Message* clone() const override;
};

class HeadlightsMessage final : public mimi::HeadlightsMessage
{
public:
    explicit HeadlightsMessage(ICore &core) : mimi::HeadlightsMessage(core) {}

    void execute() const override
    {
        core.getHeadlightsController().turnOn(red, green, blue);
    }

    Message* clone() const override {
        return new HeadlightsMessage(*this);
    }
};

class DriveMotorsMessage final : public mimi::DriveMotorsMessage
{
public:
    explicit DriveMotorsMessage(ICore &core) : mimi::DriveMotorsMessage(core) {}

    void execute() const override
    {
        core.getMotorsController().runMotors(speedLeft, speedRight);
    }

    Message* clone() const override {
        return new DriveMotorsMessage(*this);
    }
};

class DistanceRequestMessage final : public mimi::DistanceRequestMessage
{
public:
    explicit DistanceRequestMessage(ICore &core) : mimi::DistanceRequestMessage(core) {}

    void execute() const override
    {
        core.getUltrasonicController().startMeasuring(periodMillis);
    }

    Message* clone() const override
    {
        return new DistanceRequestMessage(*this);
    }
};

class ShowAnimationMessage final : public mimi::ShowAnimationMessage
{
public:
    explicit ShowAnimationMessage(ICore &core) : mimi::ShowAnimationMessage(core) {}

    void execute() const override
    {
        core.getDisplayController().startAnimationAsync(animationType);
    }

    Message* clone() const override {
        return new ShowAnimationMessage(*this);
    }
};

class PrintTextMessage final : public mimi::PrintTextMessage
{
public:
    explicit PrintTextMessage(ICore &core) : mimi::PrintTextMessage(core) {}

    void execute() const override
    {
        core.getDisplayController().stopAnimation();
        core.getDisplayController().print(text);
    }

    Message* clone() const override {
        return new PrintTextMessage(*this);
    }
};

} // namespace mimi

#endif //TINYBIT_MESSAGES_H
