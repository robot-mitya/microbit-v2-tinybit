#ifndef BT_COM_CONTROLLER_H
#define BT_COM_CONTROLLER_H

#include "../constants.h"
#include "../icore.h"
#include "codal-microbit-v2/model/MicroBit.h"

namespace mimi::microbit
{

class BtComController final : public IComController
{
    volatile bool running = false;
    static BtComController* instance; // NOLINT(*-dynamic-static-initializers)
    static void fiberRunner();

    MicroBit& uBit;

    const char* readLine(int& status);

public:
    explicit BtComController(MicroBit& uBit, ICore &core) : IComController(core), uBit(uBit) {}
    int getControllerId() override { return language::CONTROLLER_ID_BLUETOOTH; }

    void init() override;
    void start() override;
    void stop() override;
    void sendLine(const char *line) override;
};

} // namespace mimi::microbit

#endif //BT_COM_CONTROLLER_H
