#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MicroBit.h"

namespace mimi
{

    class Interpreter {
        MicroBit& uBit;
        volatile bool running = false;

        static Interpreter* instance; // NOLINT(*-dynamic-static-initializers)

        static constexpr int RxBufferSize = 80;
        static constexpr int MaxLineLength = 80;
        char lineBuffer[MaxLineLength + 1] = {};
        const char* readLine();
        void processLine(const char* line) const;

        static void fiberRunner();

    public:
        explicit Interpreter(MicroBit &uBit) : uBit(uBit) {}

        void start();
        void stop();
    };

} // namespace mimi

#endif // INTERPRETER_H
