#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "constants.h"

namespace mimi
{

class ICore;

class IController
{
protected:
    ICore& core;
    char outputBuffer[language::MAX_LINE_LENGTH + 1] = "\0";
public:
    explicit IController(ICore &core) : core(core) {}
    virtual ~IController() = default;
    virtual int getControllerId() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace mimi

#endif //ICONTROLLER_H
