#ifndef TEST_LANGUAGE_CONTROLLER_H
#define TEST_LANGUAGE_CONTROLLER_H

#include "tests.h"
#include "dummy_mocks.h"

namespace mimi::tests::language_controller
{

class FakeMessage : public Message
{
public:
    const int number;
    explicit FakeMessage(ICore &core, const int number) : Message(core), number(number) {}
    int parse(const char* line, const unsigned int argsStartPos) override
    {
        (void)line;
        (void)argsStartPos;
        return 0;
    }
    void execute() const override {}
};

class FakeMessage123 final : public FakeMessage
{
public:
    explicit FakeMessage123(ICore& core) : FakeMessage(core, 123) {}
};

class FakeMessage456 final : public FakeMessage
{
public:
    explicit FakeMessage456(ICore& core) : FakeMessage(core, 456) {}
};

class FakeMessage789 final : public FakeMessage
{
public:
    explicit FakeMessage789(ICore& core) : FakeMessage(core, 789) {}
};

class FakeLanguageController final : public DummyLanguageController
{
    static constexpr int COMMANDS_COUNT = 3;
    CommandEntry commandEntries[COMMANDS_COUNT];
public:
    explicit FakeLanguageController(ICore& core) : DummyLanguageController(core, commandEntries, COMMANDS_COUNT)
    {
        commandEntries[0] = {
            "789",
            [this]() -> Message* { return new FakeMessage789(this->core); }
        };
        commandEntries[1] = {
            "456",
            [this]() -> Message* { return new FakeMessage456(this->core); }
        };
        commandEntries[2] = {
            "123",
            [this]() -> Message* { return new FakeMessage123(this->core); }
        };
    }

    void start() override {}
    void stop() override {}
};

class FakeCore final : public ICore {
    FakeLanguageController fakeLanguageController;
    DummyQueueController dummyQueueController;
    DummyHeadlightsController dummyHeadlightsController;
    DummyMotorsController dummyMotorsController;
    DummyDisplayController dummyDisplayController;
    DummyUsbComController dummyUsbComController;
public:
    FakeCore() :
        fakeLanguageController(*this),
        dummyQueueController(*this),
        dummyHeadlightsController(*this),
        dummyMotorsController(*this),
        dummyDisplayController(*this),
        dummyUsbComController(*this) {}

    ILanguageController& getLanguageController() override { return fakeLanguageController; }
    IQueueController& getQueueController() override { return dummyQueueController; }
    IHeadlightsController& getHeadlightsController() override { return dummyHeadlightsController; }
    IMotorsController& getMotorsController() override { return dummyMotorsController; }
    IDisplayController& getDisplayController() override { return dummyDisplayController; }
    IComController& getUsbComController() override { return dummyUsbComController; }
};

// ReSharper disable once CppDFAConstantFunctionResult
inline int test_uninitialized_command_processor()
{
    FakeCore core;
    const FakeLanguageController processor(core);
    // ReSharper disable once CppLocalVariableMayBeConst
    Message * message = processor.createMessage("123");
    ASSERT_EQ(true, message == nullptr, "createMessage(mnemonic:\"123\") returns nullptr");
    message = processor.createMessage("567");
    ASSERT_EQ(true, message == nullptr, "createMessage(mnemonic:\"456\") returns nullptr");
    message = processor.createMessage("789");
    ASSERT_EQ(true, message == nullptr, "createMessage(mnemonic:\"789\") returns nullptr");
    return 0;
}

inline int test_command_processor_on_nonexisting_mnemonic()
{
    FakeCore core;
    FakeLanguageController processor(core);
    processor.init();
    const Message * message = processor.createMessage("abc");
    ASSERT_EQ(true, message == nullptr, "createMessage(mnemonic:\"abc\") returns nullptr");
    return 0;
}

inline int test_command_processor_positive_scenarios()
{
    FakeCore core;
    FakeLanguageController processor(core);
    processor.init();

    Message* message = processor.createMessage("123");
    ASSERT_EQ(123, (static_cast<FakeMessage*>(message))->number,
        "createMessage(mnemonic:\"123\").number returns 123");

    message = processor.createMessage("456");
    ASSERT_EQ(456, (static_cast<FakeMessage*>(message))->number,
        "createMessage(mnemonic:\"456\").number returns 456");

    message = processor.createMessage("789");
    ASSERT_EQ(789, (static_cast<FakeMessage*>(message))->number,
        "createMessage(mnemonic:\"789\").number returns 789");

    return 0;
}

} // namespace mimi

#endif //TEST_LANGUAGE_CONTROLLER_H
