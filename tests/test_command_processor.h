#ifndef TEST_COMMAND_PROCESSOR_H
#define TEST_COMMAND_PROCESSOR_H

#include "tests.h"
#include "dummy_mocks.h"

namespace mimi::tests::command_processor
{
    class DummyMessage : public Message
    {
    public:
        const int number;
        explicit DummyMessage(ICore &core, const int number) : Message(core), number(number) {}
        int parse(const char* line, const unsigned int argsStartPos) override
        {
            (void)line;
            (void)argsStartPos;
            return 0;
        }
        void execute() const override {}
    };

    class DummyMessage123 final : public DummyMessage
    {
    public:
        explicit DummyMessage123(ICore& core) : DummyMessage(core, 123) {}
    };

    class DummyMessage456 final : public DummyMessage
    {
    public:
        explicit DummyMessage456(ICore& core) : DummyMessage(core, 456) {}
    };

    class DummyMessage789 final : public DummyMessage
    {
    public:
        explicit DummyMessage789(ICore& core) : DummyMessage(core, 789) {}
    };

    class DummyCommandProcessor final : public ICommandProcessor
    {
        static constexpr int COMMANDS_COUNT = 3;
        DummyCore core;
        CommandEntry commandEntries[COMMANDS_COUNT];
    public:
        DummyCommandProcessor() : ICommandProcessor(commandEntries, COMMANDS_COUNT)
        {
            commandEntries[0] = {
                "789",
                [this]() -> Message* { return new DummyMessage789(this->core); }
            };
            commandEntries[1] = {
                "456",
                [this]() -> Message* { return new DummyMessage456(this->core); }
            };
            commandEntries[2] = {
                "123",
                [this]() -> Message* { return new DummyMessage123(this->core); }
            };
        }

        void start() override {}
        void stop() override {}
    };

    // ReSharper disable once CppDFAConstantFunctionResult
    inline int test_uninitialized_command_processor()
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        DummyCommandProcessor processor;
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
        DummyCommandProcessor processor;
        processor.init();
        const Message * message = processor.createMessage("abc");
        ASSERT_EQ(true, message == nullptr, "createMessage(mnemonic:\"abc\") returns nullptr");
        return 0;
    }

    inline int test_command_processor_positive_scenarios()
    {
        DummyCommandProcessor processor;
        processor.init();

        Message* message = processor.createMessage("123");
        ASSERT_EQ(123, (static_cast<DummyMessage*>(message))->number,
            "createMessage(mnemonic:\"123\").number returns 123");

        message = processor.createMessage("456");
        ASSERT_EQ(456, (static_cast<DummyMessage*>(message))->number,
            "createMessage(mnemonic:\"456\").number returns 456");

        message = processor.createMessage("789");
        ASSERT_EQ(789, (static_cast<DummyMessage*>(message))->number,
            "createMessage(mnemonic:\"789\").number returns 789");

        return 0;
    }

} // namespace mimi

#endif //TEST_COMMAND_PROCESSOR_H
