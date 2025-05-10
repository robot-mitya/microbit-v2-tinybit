#include "interpreter.h"

#include "ManagedString.h"

#define RX_BUFFER_SIZE 80
#define MAX_LINE_LENGTH 80
#define MAX_ARGS 10

Interpreter* Interpreter::instance = nullptr;

ManagedString Interpreter::readLine()
{
    ManagedString buffer = "";
    while (true)
    {
        while (!uBit.serial.isReadable())
            uBit.sleep(1);

        char c = uBit.serial.getc();

        if (c == '\r' || c == '\n')
            break;

        buffer = buffer + c;

        if (buffer.length() >= MAX_LINE_LENGTH)
        {
            //TODO DZZ: Generate error message!
            break;
        }
    }
    return buffer;
}

void Interpreter::processLine(const ManagedString & line) {
    uBit.serial.printf(("ECHO: " + line + "\r\n").toCharArray());
}

void Interpreter::fiberRunner() {
    if (!instance) return;
    while (instance->running) {
        if (instance->uBit.serial.isReadable()) {
            ManagedString line = instance->readLine();
            if (line.length() > 0)
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
    uBit.serial.setRxBufferSize(RX_BUFFER_SIZE);
    uBit.serial.printf("Interpreter started\r\n");
    running = true;
    create_fiber(fiberRunner);
}

void Interpreter::stop()
{
    running = false;
    uBit.serial.printf("Interpreter stopped\r\n");
}
