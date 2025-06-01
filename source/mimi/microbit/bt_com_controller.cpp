#include "bt_com_controller.h"

#include <cstring>

using namespace mimi::microbit;

BtComController *BtComController::instance = nullptr;

const char *BtComController::readLine(int& status)
{
    status = language::PARSE_STATUS_OK;
    int pos = 0;
    while (uart != nullptr)
    {
        while (!uart->isReadable())
            fiber_sleep(1);

        const char c = uart->getc();
        if (c == '\r' || c == '\n') break;

        lineBuffer[pos++] = c;
        if (pos >= MaxLineLength)
        {
            status = language::PARSE_STATUS_LINE_TOO_LONG;
            break;
        }
    }

    lineBuffer[pos] = '\0'; // null-terminate
    return lineBuffer;
}

void BtComController::fiberRunner()
{
    while (instance != nullptr && instance->uart != nullptr && instance->running)
    {
        if (instance->uart->isReadable())
        {
            int status;
            const char *line = instance->readLine(status);
            if (status == language::PARSE_STATUS_OK && strlen(line) > 0)
                status = instance->processLine(line);
        }
        fiber_sleep(1);
    }
}

void BtComController::init()
{
    instance = this;
    core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
}


void BtComController::start()
{
    if (running) return;
    running = true;
    uart = new MicroBitUARTService(*uBit.ble, RxBufferSize, TxBufferSize);
    create_fiber(fiberRunner);
    core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
}

void BtComController::stop()
{
    delete uart;
    uart = nullptr;
    running = false;
    core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
}

void BtComController::sendLine(const char *line)
{
    if (uart != nullptr) uart->send(line);
}
