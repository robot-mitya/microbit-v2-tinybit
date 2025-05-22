#ifndef FAKE_MOCKS_H
#define FAKE_MOCKS_H

#include "dummy_mocks.h"
#include "../source/mimi/icore.h"

namespace mimi::tests
{

class FakeLanguageController final : public ILanguageController
{
public:
    explicit FakeLanguageController(ICore& core) : ILanguageController(core, nullptr, 0) {}
    void start() override {}
    void stop() override {}
};

class FakeQueueController final : public IQueueController
{
    DummyLock lock;
public:
    explicit FakeQueueController(ICore& core) : IQueueController(core, lock) {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class FakeHeadlightsController final : public IHeadlightsController
{
public:
    explicit FakeHeadlightsController(ICore& core) : IHeadlightsController(core) {}
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
    explicit FakeMotorsController(ICore& core) : IMotorsController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
    void runMotors(int, int) override {}
    void stopMotors() override {}
};

class FakeDisplayController final : public IDisplayController
{
public:
    explicit FakeDisplayController(ICore& core) : IDisplayController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
    IFrameAnimation* startAnimationAsync(AnimationType) override { return nullptr; }
    void stopAnimation() override {}
};

class FakeUsbComController final : public IComController
{
// protected:
//     void processLine(const char *line) const override;
public:
    explicit FakeUsbComController(ICore& core) : IComController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
};

class FakeCore final : public ICore {
    FakeLanguageController fakeLanguageController;
    FakeQueueController fakeQueueController;
    FakeHeadlightsController fakeHeadlightsController;
    FakeMotorsController fakeMotorsController;
    FakeDisplayController fakeDisplayController;
    FakeUsbComController fakeUsbComController;
public:
    FakeCore() :
        fakeLanguageController(*this),
        fakeQueueController(*this),
        fakeHeadlightsController(*this),
        fakeMotorsController(*this),
        fakeDisplayController(*this),
        fakeUsbComController(*this) {}

    ILanguageController& getLanguageController() override { return fakeLanguageController; }
    IQueueController& getQueueController() override { return fakeQueueController; }
    IHeadlightsController& getHeadlightsController() override { return fakeHeadlightsController; }
    IMotorsController& getMotorsController() override { return fakeMotorsController; }
    IDisplayController& getDisplayController() override { return fakeDisplayController; }
    IComController& getUsbComController() override { return fakeUsbComController; }
};

} // namespace mimi::tests

#endif //FAKE_MOCKS_H
