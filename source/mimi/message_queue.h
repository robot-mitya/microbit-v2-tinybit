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

class Message;

template<typename T>
class MessageQueue
{
    static constexpr int Capacity = 64;
    T* buffer[Capacity] = {nullptr};
    int head = 0;
    int tail = 0;
    int count = 0;
    ILock& lock;

public:
    static_assert(std::is_base_of<Message, T>::value, "T must inherit from Message");

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

    bool enqueue(T* msg)
    {
        lock.wait();
        if (count == Capacity) {
            lock.notify();
            return false;
        }
        buffer[tail] = static_cast<T*>(msg->clone());
        tail = (tail + 1) % Capacity;
        count++;
        lock.notify();
        return true;
    }

    T* dequeue()
    {
        lock.wait();
        if (count == 0)
        {
            lock.notify();
            return nullptr;
        }
        T* msg = buffer[head];
        buffer[head] = nullptr;
        head = (head + 1) % Capacity;
        count--;
        lock.notify();
        return msg;
    }

    void clear()
    {
        lock.wait();
        for (T* & i : buffer) {
            i = nullptr;
        }
        head = 0;
        tail = 0;
        count = 0;
        lock.notify();
    }
};

} // namespace mimi

#endif // MESSAGE_QUEUE_H
