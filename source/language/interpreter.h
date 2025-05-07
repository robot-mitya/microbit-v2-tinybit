#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MicroBit.h"

class Interpreter {
private:
    MicroBit& uBit;

    void onSerialLine(MicroBitEvent) {
        ManagedString line = uBit.serial.readUntil(ManagedString("\n"));
        processLine(line);
    }

    void processLine(const ManagedString& line) {
        uBit.serial.printf("%s\r\n", line.toCharArray());
    }

public:
    Interpreter(MicroBit& uBit) : uBit(uBit) {}

    void start() {
        uBit.serial.setRxBufferSize(64);
        uBit.serial.eventOn(ManagedString("\n"));
        uBit.messageBus.listen(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_DELIM_MATCH, this, &Interpreter::onSerialLine);
        uBit.serial.printf("Interpreter started\r\n");
    }

    void stop() {
        uBit.messageBus.ignore(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_DELIM_MATCH, this, &Interpreter::onSerialLine);
    }
};

#endif // INTERPRETER_H
