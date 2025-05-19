//
// Created by dmitrydzz on 5/15/25.
//

#ifndef TESTS_H
#define TESTS_H

#include "../source/controllers/icore.h"

#define USE_COLORS 1

#if USE_COLORS
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED   "\033[1;31m"
#define COLOR_RESET "\033[0m"
#else
#define COLOR_GREEN ""
#define COLOR_RED   ""
#define COLOR_RESET ""
#endif

#define ASSERT_EQ(expected, actual, description) \
do { \
std::cout << __func__ << "(): "; \
if ((expected) != (actual)) { \
std::cout << COLOR_RED << description << " [FAIL]" << COLOR_RESET \
<< ": expected " << (expected) << ", got " << (actual) \
<< std::endl; \
return 1; \
} else { \
std::cout << COLOR_GREEN << description << " [OK]" << COLOR_RESET \
<< std::endl; \
} \
} while (0)

namespace mimi::tests
{

class FakeCommandProcessor final : public ICommandProcessor
{
public:
    FakeCommandProcessor() : ICommandProcessor(nullptr, 0) {}
    void start() override {}
    void stop() override {}
};

class FakeQueueController final : public IQueueController
{
public:
    FakeQueueController() : IQueueController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class FakeHeadlightsController final : public IHeadlightsController
{
public:
    FakeHeadlightsController() : IHeadlightsController() {}
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

class FakeMotorsController final : public IMotorsController
{
public:
    FakeMotorsController() : IMotorsController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
    void runMotors(int, int) override {}
    void stopMotors() override {}
};

class FakeDisplayController final : public IDisplayController
{
public:
    FakeDisplayController() : IDisplayController() {}
    void init() override {}
    void start() override {}
    void stop() override {}
    IFrameAnimation* startAnimationAsync(AnimationType) override { return nullptr; }
    void stopAnimation() override {}
};

class FakeCore final : public ICore {
    FakeCommandProcessor fakeCommandProcessor;
    FakeQueueController fakeQueueController;
    FakeHeadlightsController fakeHeadlightsController;
    FakeMotorsController fakeMotorsController;
    FakeDisplayController fakeDisplayController;
public:
    ICommandProcessor& getCommandProcessor() override { return fakeCommandProcessor; }
    IQueueController& getQueueController() override { return fakeQueueController; }
    IHeadlightsController& getHeadlightsController() override { return fakeHeadlightsController; }
    IMotorsController& getMotorsController() override { return fakeMotorsController; }
    IDisplayController& getDisplayController() override { return fakeDisplayController; }
};

} // namespace mimi::tests

#endif //TESTS_H
