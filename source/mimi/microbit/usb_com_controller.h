#ifndef USB_COM_CONTROLLER_H
#define USB_COM_CONTROLLER_H

#include "../constants.h"
#include "../icore.h"
#include "codal-microbit-v2/model/MicroBit.h"

namespace mimi::microbit
{

class UsbComController final : public IComController
{
    MicroBit& uBit;
    volatile bool running = false;

    static UsbComController* instance; // NOLINT(*-dynamic-static-initializers)

    static constexpr int MaxLineLength = language::MAX_LINE_LENGTH;
    static constexpr int RxBufferSize = MaxLineLength;
    char lineBuffer[MaxLineLength + 1] = {};

    const char* readLine(int& status);
    void reportStatus(int status) const override;

    static void fiberRunner();

protected:
    // int processLine(const char *line) const override
    // {
    //     uBit.serial.printf("ECHO: %s\r\n",  line);
    //     return 0;
    // }

public:
    explicit UsbComController(MicroBit& uBit, ICore &core) : IComController(core), uBit(uBit) {}
    void init() override;
    void start() override;
    void stop() override;
};

} // namespace mimi::microbit

#endif //USB_COM_CONTROLLER_H
