#include "interpreter.h"

using namespace mimi;

Interpreter *Interpreter::instance = nullptr;

const char *Interpreter::readLine()
{
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
            //TODO DZZ: Generate error message!
            break;
        }
    }

    lineBuffer[pos] = '\0'; // null-terminate
    return lineBuffer;
}

void Interpreter::processLine(const char *line) const
{
    uBit.serial.printf("Echo: %s\r\n", line);
}

void Interpreter::fiberRunner()
{
    if (!instance)
        return;
    while (instance->running)
    {
        if (instance->uBit.serial.isReadable())
        {
            const char *line = instance->readLine();
            if (strlen(line) > 0)
                instance->processLine(line);
        }
        fiber_sleep(1);
    }
}

void Interpreter::start()
{
    if (running)
        return;
    instance = this;
    uBit.serial.setRxBufferSize(RxBufferSize);
    uBit.serial.printf("Interpreter started\r\n");
    running = true;
    create_fiber(fiberRunner);
}

void Interpreter::stop()
{
    running = false;
    uBit.serial.printf("Interpreter stopped\r\n");
}
