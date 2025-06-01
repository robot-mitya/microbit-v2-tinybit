#ifndef ICOM_CONTROLLER_H
#define ICOM_CONTROLLER_H

#include "icontroller.h"
#include "ilanguage_controller.h"
#include "constants.h"

namespace mimi
{

class IComController : public IController
{
protected:
    static constexpr int MaxLineLength = language::MAX_LINE_LENGTH;
    static constexpr int RxBufferSize = MaxLineLength;
    static constexpr int TxBufferSize = MaxLineLength;
    char lineBuffer[MaxLineLength + 1] = {};

    int processLine(const char *line) const;
public:
    explicit IComController(ICore &core) : IController(core) {}
    virtual void sendLine(const char *line) = 0;
};

} // namespace mimi

#endif //ICOM_CONTROLLER_H
