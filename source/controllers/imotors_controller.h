#ifndef IMOTORS_CONTROLLER_H
#define IMOTORS_CONTROLLER_H

namespace mimi
{

class ICore;

class IMotorsController
{
public:
    virtual ~IMotorsController() = default;

    virtual void run(int speedLeft, int speedRight) = 0;
    virtual void stop() = 0;
};

} // namespace mimi

#endif //IMOTORS_CONTROLLER_H
