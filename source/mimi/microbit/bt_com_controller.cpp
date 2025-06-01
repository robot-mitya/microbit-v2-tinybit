#include "bt_com_controller.h"

#include <cstring>

using namespace mimi::microbit;

BtComController *BtComController::instance = nullptr;

const char *BtComController::readLine(int& status)
{
    status = language::PARSE_STATUS_OK;
    // int pos = 0;
    // while (true)
    // {
    //     while (!uBit.serial.isReadable())
    //         fiber_sleep(1);
    //
    //     const char c = uBit.serial.getc();
    //     if (c == '\r' || c == '\n') break;
    //
    //     lineBuffer[pos++] = c;
    //     if (pos >= MaxLineLength)
    //     {
    //         status = language::PARSE_STATUS_LINE_TOO_LONG;
    //         break;
    //     }
    // }
    //
    // lineBuffer[pos] = '\0'; // null-terminate
    return lineBuffer;
}

void BtComController::fiberRunner()
{
    if (!instance) return;
    while (instance->running)
    {
        // if (instance->uBit.serial.isReadable())
        // {
        //     int status;
        //     const char *line = instance->readLine(status);
        //     if (status == language::PARSE_STATUS_OK && strlen(line) > 0)
        //         status = instance->processLine(line);
        // }
        fiber_sleep(1);
    }
}

void BtComController::init()
{
    instance = this;
    uBit.serial.setRxBufferSize(RxBufferSize);

    uBit.serial.printf("DEBUG [BtComController] => MICROBIT_BLE_ENABLED=%d\r\n", MICROBIT_BLE_ENABLED);
    uBit.serial.printf("DEBUG [BtComController] => MICROBIT_BLE_PAIRING_MODE=%d\r\n", MICROBIT_BLE_PAIRING_MODE);
    uBit.serial.printf("DEBUG [BtComController] => MICROBIT_BLE_NORDIC_STYLE_UART=%d\r\n", MICROBIT_BLE_NORDIC_STYLE_UART);

    core.sendInfo(getControllerId(), language::CONTROLLER_INIT_STATUS_OK);
}


void BtComController::start()
{
    if (running) return;
    running = true;
    create_fiber(fiberRunner);
    core.sendInfo(getControllerId(), language::CONTROLLER_START_STATUS_OK);
    uBit.serial.printf("DEBUG => BtComController has been started\r\n");
}

void BtComController::stop()
{
    running = false;
    core.sendInfo(getControllerId(), language::CONTROLLER_STOP_STATUS_OK);
}

void BtComController::sendLine(const char *line)
{
    // uBit.serial.printf(line);
}
