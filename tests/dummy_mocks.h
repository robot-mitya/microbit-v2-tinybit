//
// Created by dmitrydzz on 5/20/25.
//

#ifndef DUMMY_MOCKS_H
#define DUMMY_MOCKS_H

#include "../source/controllers/icore.h"

namespace mimi::tests
{

class DummyCommandProcessor : public ICommandProcessor
{
protected:
    DummyCommandProcessor(ICore &core, CommandEntry *table, const int count) : ICommandProcessor(core, table, count) {}
    // void processLine(const char*) const override {}
public:
    DummyCommandProcessor(ICore& core) : ICommandProcessor(core, nullptr, 0) {}
    void start() override {}
    void stop() override {}
};

class DummyQueueController final : public IQueueController
{
public:
    explicit DummyQueueController(ICore& core) : IQueueController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class DummyHeadlightsController final : public IHeadlightsController
{
public:
    explicit DummyHeadlightsController(ICore& core) : IHeadlightsController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}

    void turnOn(uint8_t, uint8_t, uint8_t) override {}
    void turnOff() override {}
    bool isTurnedOn() override { return false; }
    uint8_t getRed() override { return 0; }
    uint8_t getGreen() override { return 0; }
    uint8_t getBlue() override { return 0; }
};

class DummyMotorsController final : public IMotorsController
{
public:
    explicit DummyMotorsController(ICore& core) : IMotorsController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
    void runMotors(int, int) override {}
    void stopMotors() override {}
};

class DummyDisplayController final : public IDisplayController
{
public:
    explicit DummyDisplayController(ICore& core) : IDisplayController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
    IFrameAnimation* startAnimationAsync(AnimationType) override { return nullptr; }
    void stopAnimation() override {}
};

class DummyUsbComController final : public IUsbComController
{
protected:
    void processLine(const char*) const override {}
public:
    explicit DummyUsbComController(ICore& core) : IUsbComController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class DummyCore final : public ICore {
    DummyCommandProcessor dummyCommandProcessor;
    DummyQueueController dummyQueueController;
    DummyHeadlightsController dummyHeadlightsController;
    DummyMotorsController dummyMotorsController;
    DummyDisplayController dummyDisplayController;
    DummyUsbComController dummyUsbComController;
public:
    DummyCore() :
        dummyCommandProcessor(*this),
        dummyQueueController(*this),
        dummyHeadlightsController(*this),
        dummyMotorsController(*this),
        dummyDisplayController(*this),
        dummyUsbComController(*this) {}

    ICommandProcessor& getCommandProcessor() override { return dummyCommandProcessor; }
    IQueueController& getQueueController() override { return dummyQueueController; }
    IHeadlightsController& getHeadlightsController() override { return dummyHeadlightsController; }
    IMotorsController& getMotorsController() override { return dummyMotorsController; }
    IDisplayController& getDisplayController() override { return dummyDisplayController; }
    IUsbComController& getUsbComController() override { return dummyUsbComController; }
};

} // namespace mimi::tests

#endif //DUMMY_MOCKS_H
