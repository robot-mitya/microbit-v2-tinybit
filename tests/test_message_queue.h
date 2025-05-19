// ReSharper disable CppUseAuto
#ifndef TEST_MESSAGE_QUEUE_H
#define TEST_MESSAGE_QUEUE_H

#include <iostream>
#include "../source/language/message_queue.h"
#include "tests.h"

namespace mimi::tests::message_queue
{

    class DummyLock final : public ILock {
    public:
        void wait() override {}
        void notify() override {}
    };

    class DummyMessage final : public Message
    {
    public:
        explicit DummyMessage(ICore& core) : Message(core) {}
        int parse(const char* line, const unsigned int argsStartPos) override
        {
            (void)line;
            (void)argsStartPos;
            return 0;
        }
        void execute() const override {}
    };

    inline int test_message_queue_basic_positive()
    {
        DummyCore core;
        DummyLock lock;
        DummyMessage message(core);
        MessageQueue queue(lock);

        ASSERT_EQ(64, MessageQueue::capacity(), "Queue capacity");
        ASSERT_EQ(0, queue.size(), "Size of empty");
        ASSERT_EQ(true, queue.isEmpty(), "IsEmpty for empty");
        ASSERT_EQ(false, queue.isFull(), "IsFull for empty");

        const int enqueueResult = queue.enqueue(&message);
        ASSERT_EQ(true, enqueueResult, "Enqueued");
        ASSERT_EQ(1, queue.size(), "Queue size");
        ASSERT_EQ(false, queue.isEmpty(), "IsEmpty for non-empty");
        ASSERT_EQ(false, queue.isFull(), "IsFull for non-empty");

        const Message * dequedMessage = queue.dequeue();
        ASSERT_EQ(true, dequedMessage != nullptr, "Dequeued message is not null");
        ASSERT_EQ(0, queue.size(), "Empty after dequed");
        ASSERT_EQ(true, queue.isEmpty(), "IsEmpty is true");
        ASSERT_EQ(false, queue.isFull(), "IsFull is false");

        return 0;
    }

    inline int test_message_queue_enqueue_scenarios()
    {
        DummyCore core;
        DummyLock lock;
        DummyMessage message(core);
        MessageQueue queue(lock);

        for (int i = 0; i < MessageQueue::capacity(); i++)
        {
            const int enqueueResult = queue.enqueue(&message);
            if (i == 0)
            {
                ASSERT_EQ(true, enqueueResult, "Enqueued first: true");
                ASSERT_EQ(1, queue.size(), "Enqueued first: size == 1");
                ASSERT_EQ(false, queue.isEmpty(), "Enqueued first: non-empty");
                ASSERT_EQ(false, queue.isFull(), "Enqueued first: not-filled");
            } else if (i == MessageQueue::capacity() - 1)
            {
                ASSERT_EQ(true, enqueueResult, "Enqueued last: true");
                ASSERT_EQ(MessageQueue::capacity(), queue.size(), "Enqueued last: size == Capacity");
                ASSERT_EQ(false, queue.isEmpty(), "Enqueued last: non-empty");
                ASSERT_EQ(true, queue.isFull(), "Enqueued last: filled");
            }
        }

        const int enqueueResult = queue.enqueue(&message);
        ASSERT_EQ(false, enqueueResult, "Enqueued filled: false");

        return 0;
    }

    inline int test_message_queue_dequeue_scenarios()
    {
        DummyCore core;
        DummyLock lock;
        DummyMessage message(core);
        MessageQueue queue(lock);

        for (int i = 0; i < MessageQueue::capacity(); i++)
        {
            queue.enqueue(&message);
        }

        for (int i = 0; i < MessageQueue::capacity(); i++)
        {
            const Message* dequeuedMessage = queue.dequeue();
            if (i == 0)
            {
                ASSERT_EQ(true, dequeuedMessage != nullptr, "Dequeued first: true");
                ASSERT_EQ(MessageQueue::capacity() - 1, queue.size(), "Dequeued first: size == capacity-1");
                ASSERT_EQ(false, queue.isEmpty(), "Dequeued first: non-empty");
                ASSERT_EQ(false, queue.isFull(), "Dequeued first: not-filled");
            } else if (i == MessageQueue::capacity() - 1)
            {
                ASSERT_EQ(true, dequeuedMessage != nullptr, "Dequeued last: true");
                ASSERT_EQ(0, queue.size(), "Dequeued last: size == 0");
                ASSERT_EQ(true, queue.isEmpty(), "Dequeued last: empty");
                ASSERT_EQ(false, queue.isFull(), "Dequeued last: not-filled");
            }
        }

        const Message* dequeuedMessage = queue.dequeue();
        ASSERT_EQ(true, dequeuedMessage == nullptr, "Dequeued empty: nullptr");

        return 0;
    }

} // namespace mimi

#endif //TEST_MESSAGE_QUEUE_H
