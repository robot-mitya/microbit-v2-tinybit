//
// Created by dmitrydzz on 5/20/25.
//

#ifndef DUMMY_MOCKS_H
#define DUMMY_MOCKS_H

#include "../source/controllers/icore.h"

namespace mimi::tests
{

class DummyCommandProcessor final : public ICommandProcessor
{
public:
    DummyCommandProcessor() : ICommandProcessor(nullptr, 0) {}
    void start() override {}
    void stop() override {}
};

class DummyQueueController final : public IQueueController
{
public:
    DummyQueueController() : IQueueController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class DummyHeadlightsController final : public IHeadlightsController
{
public:
    DummyHeadlightsController() : IHeadlightsController() {}
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
    DummyMotorsController() : IMotorsController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
    void runMotors(int, int) override {}
    void stopMotors() override {}
};

class DummyDisplayController final : public IDisplayController
{
public:
    DummyDisplayController() : IDisplayController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
    IFrameAnimation* startAnimationAsync(AnimationType) override { return nullptr; }
    void stopAnimation() override {}
};

class DummyCore final : public ICore {
    DummyCommandProcessor dummyCommandProcessor;
    DummyQueueController dummyQueueController;
    DummyHeadlightsController dummyHeadlightsController;
    DummyMotorsController dummyMotorsController;
    DummyDisplayController dummyDisplayController;
public:
    ICommandProcessor& getCommandProcessor() override { return dummyCommandProcessor; }
    IQueueController& getQueueController() override { return dummyQueueController; }
    IHeadlightsController& getHeadlightsController() override { return dummyHeadlightsController; }
    IMotorsController& getMotorsController() override { return dummyMotorsController; }
    IDisplayController& getDisplayController() override { return dummyDisplayController; }
};

} // namespace mimi::tests

#endif //DUMMY_MOCKS_H
