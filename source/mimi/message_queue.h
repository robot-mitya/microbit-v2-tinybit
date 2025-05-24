#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

namespace mimi
{

    class ILock
    {
    public:
        virtual void wait() = 0;
        virtual void notify() = 0;
        virtual ~ILock() = default;
    };

    class InputMessage;

    class MessageQueue {
        static constexpr int Capacity = 64;
        InputMessage* buffer[Capacity] = {nullptr};
        int head = 0;
        int tail = 0;
        int count = 0;
        ILock& lock;

    public:
        explicit MessageQueue(ILock& lockRef) : lock(lockRef) {}

        bool isEmpty() const
        {
            lock.wait();
            const bool result = count == 0;
            lock.notify();
            return result;
        }

        bool isFull() const
        {
            lock.wait();
            const bool result = count == Capacity;
            lock.notify();
            return result;
        }

        int size() const
        {
            lock.wait();
            const int result = count;
            lock.notify();
            return result;
        }

        static int capacity() { return Capacity; }

        bool enqueue(InputMessage* msg) {
            lock.wait();
            if (count == Capacity) {
                lock.notify();
                return false;
            }
            buffer[tail] = msg;
            tail = (tail + 1) % Capacity;
            count++;
            lock.notify();
            return true;
        }

        InputMessage* dequeue() {
            lock.wait();
            if (count == 0) {
                lock.notify();
                return nullptr;
            }
            InputMessage* msg = buffer[head];
            buffer[head] = nullptr;
            head = (head + 1) % Capacity;
            count--;
            lock.notify();
            return msg;
        }
    };

} // namespace mimi

#endif // MESSAGE_QUEUE_H
