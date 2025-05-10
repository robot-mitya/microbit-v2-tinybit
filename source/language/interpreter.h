#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MicroBit.h"

class Interpreter {
    MicroBit& uBit;
    volatile bool running = false;

    static Interpreter* instance;

    ManagedString readLine();

    void processLine(const ManagedString &line);

    static void fiberRunner();

public:
    explicit Interpreter(MicroBit &uBit) : uBit(uBit) {}

    void start();
    void stop();
};

#endif // INTERPRETER_H
