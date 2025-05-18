#ifndef TEST_COMMAND_PROCESSOR_H
#define TEST_COMMAND_PROCESSOR_H

#include "tests.h"
#include "../source/controllers/icommand_processor.h"

namespace mimi::tests::command_processor
{
    class DummyMessage : public Message
    {
    public:
        const int number;
        explicit DummyMessage(const int number) : number(number) {}
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
        DummyMessage123() : DummyMessage(123) {}
    };

    class DummyMessage456 final : public DummyMessage
    {
    public:
        DummyMessage456() : DummyMessage(456) {}
    };

    class DummyMessage789 final : public DummyMessage
    {
    public:
        DummyMessage789() : DummyMessage(789) {}
    };

    static CommandEntry myTable[] = {
        {"789", []() -> Message* { return new DummyMessage789(); }},
        {"456", []() -> Message* { return new DummyMessage456(); }},
        {"123", []() -> Message* { return new DummyMessage123(); }},
    };

    class DummyCommandProcessor final : public ICommandProcessor
    {
    public:
        DummyCommandProcessor() : ICommandProcessor(myTable, sizeof(myTable) / sizeof(CommandEntry))
        {
        }
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
