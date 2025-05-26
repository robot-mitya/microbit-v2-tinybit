#include "usb_com_controller.h"

#include <cstring>
#include "../constants.h"

using namespace mimi::microbit;

UsbComController *UsbComController::instance = nullptr;

const char *UsbComController::readLine(int& status)
{
    status = language::PARSE_STATUS_OK;
    int pos = 0;
    while (true)
    {
        while (!uBit.serial.isReadable())
            fiber_sleep(1);

        const char c = uBit.serial.getc();
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

void UsbComController::fiberRunner()
{
    if (!instance) return;
    while (instance->running)
    {
        if (instance->uBit.serial.isReadable())
        {
            int status;
            const char *line = instance->readLine(status);
            if (status == language::PARSE_STATUS_OK && strlen(line) > 0)
                status = instance->processLine(line);
        }
        fiber_sleep(1);
    }
}

void UsbComController::init()
{
    instance = this;
    uBit.serial.setRxBufferSize(RxBufferSize);
    uBit.serial.printf("UsbComController has been initialized\r\n");
}


void UsbComController::start()
{
    if (running) return;
    running = true;
    create_fiber(fiberRunner);
    uBit.serial.printf("UsbComController has been started\r\n");
}

void UsbComController::stop()
{
    running = false;
}

void UsbComController::sendLine(const char *line)
{
    uBit.serial.printf(line);
}
