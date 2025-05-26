#ifndef STATUS_CODES_H
#define STATUS_CODES_H

namespace mimi
{
    namespace language
    {
        constexpr int CONTROLLER_ID_LANGUAGE   = 1010;
        constexpr int CONTROLLER_ID_QUEUE      = 1020;
        constexpr int CONTROLLER_ID_HEADLIGHTS = 1030;
        constexpr int CONTROLLER_ID_MOTORS     = 1040;
        constexpr int CONTROLLER_ID_DISPLAY    = 1050;
        constexpr int CONTROLLER_ID_USB_COM    = 1060;
        constexpr int CONTROLLER_ID_BLUETOOTH  = 1070;

        constexpr int CONTROLLER_INIT_STATUS_OK = 0;
        constexpr int CONTROLLER_INIT_STATUS_WRONG_COMMAND_COUNT = -1;

        constexpr int MAX_LINE_LENGTH = 80;
        constexpr int MAX_MNEMONIC_LENGTH = 80;
        constexpr int MAX_ARGUMENT_LENGTH = 80;

        constexpr int PARSE_STATUS_OK = 0;
        constexpr int PARSE_STATUS_LINE_TOO_LONG = -1;
        constexpr int PARSE_STATUS_UNKNOWN_MNEMONIC = -2;
        constexpr int PARSE_STATUS_MISSING_ARGUMENT = -3;
        constexpr int PARSE_STATUS_WRONG_ARGUMENT = -4;
    } // namespace language
} // namespace mimi

#endif //STATUS_CODES_H
