#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MicroBit.h"

class Interpreter {
    MicroBit& uBit;
    volatile bool running = false;

    static Interpreter* instance;

    static constexpr int RxBufferSize = 80;
    static constexpr int MaxLineLength = 80;
    char lineBuffer[MaxLineLength + 1] = {0};
    const char* readLine();
    void processLine(const char* line);

    static void fiberRunner();

public:
    explicit Interpreter(MicroBit &uBit) : uBit(uBit) {}

    void start();
    void stop();
};

#endif // INTERPRETER_H
