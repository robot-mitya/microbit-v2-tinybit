//
// Created by dmitrydzz on 5/20/25.
//

#ifndef DUMMY_MOCKS_H
#define DUMMY_MOCKS_H

#include "../source/mimi/icore.h"
#include "../source/mimi/ilanguage_controller.h"
#include "../source/mimi/iqueue_controller.h"
#include "../source/mimi/iheadlights_controller.h"
#include "../source/mimi/imotors_controller.h"
#include "../source/mimi/idisplay_controller.h"
#include "../source/mimi/icom_controller.h"

namespace mimi::tests
{

class DummyLock final : public ILock
{
public:
    DummyLock() : ILock() {}
    void wait() override {}
    void notify() override {}
};

class DummyLanguageController : public ILanguageController
{
protected:
    DummyLanguageController(ICore &core, CommandEntry *table, const int count) : ILanguageController(core, table, count) {}
    // void processLine(const char*) const override {}
public:
    explicit DummyLanguageController(ICore& core) : ILanguageController(core, nullptr, 0) {}
    void start() override {}
    void stop() override {}
};

class DummyQueueController final : public IQueueController
{
    DummyLock lock;
public:
    explicit DummyQueueController(ICore& core) : IQueueController(core, lock) {}
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
    void clear() override {}
    IFrameAnimation* startAnimationAsync(AnimationType) override { return nullptr; }
    void stopAnimation() override {}
    void print(const char*) override {}
};

class DummyUsbComController final : public IComController
{
public:
    explicit DummyUsbComController(ICore& core) : IComController(core) {}
    void init() override {}
    void start() override {}
    void stop() override {}
    void sendLine(const char*) override {}
};

class DummyCore final : public ICore {
    DummyLanguageController dummyLanguageController;
    DummyQueueController dummyQueueController;
    DummyHeadlightsController dummyHeadlightsController;
    DummyMotorsController dummyMotorsController;
    DummyDisplayController dummyDisplayController;
    DummyUsbComController dummyUsbComController;
public:
    DummyCore() :
        dummyLanguageController(*this),
        dummyQueueController(*this),
        dummyHeadlightsController(*this),
        dummyMotorsController(*this),
        dummyDisplayController(*this),
        dummyUsbComController(*this) {}

    ILanguageController& getLanguageController() override { return dummyLanguageController; }
    IQueueController& getQueueController() override { return dummyQueueController; }
    IHeadlightsController& getHeadlightsController() override { return dummyHeadlightsController; }
    IMotorsController& getMotorsController() override { return dummyMotorsController; }
    IDisplayController& getDisplayController() override { return dummyDisplayController; }
    IComController& getUsbComController() override { return dummyUsbComController; }
};

} // namespace mimi::tests

#endif //DUMMY_MOCKS_H
