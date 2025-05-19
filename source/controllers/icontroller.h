#ifndef ICONTROLLER_H
#define ICONTROLLER_H

namespace mimi
{

class IController
{
    public:
        virtual ~IController() = default;
        virtual void init() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
};

} // namespace mimi

#endif //ICONTROLLER_H
