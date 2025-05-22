#ifndef ICONTROLLER_H
#define ICONTROLLER_H

namespace mimi
{

class ICore;

class IController
{
protected:
    ICore& core;
public:
    explicit IController(ICore &core) : core(core) {}
    virtual ~IController() = default;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace mimi

#endif //ICONTROLLER_H
