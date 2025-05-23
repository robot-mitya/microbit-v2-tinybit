#ifndef STATUS_CODES_H
#define STATUS_CODES_H

namespace mimi
{
    namespace language
    {
        constexpr int MAX_LINE_LENGTH = 80;
        constexpr int MAX_MNEMONIC_LENGTH = 80;

        constexpr int PARSE_STATUS_OK = 0;
        constexpr int PARSE_STATUS_LINE_TOO_LONG = -1;
        constexpr int PARSE_STATUS_UNKNOWN_MNEMONIC = -2;
        constexpr int PARSE_STATUS_MISSING_ARGUMENT = -3;
        constexpr int PARSE_STATUS_WRONG_ARGUMENT = -4;
        constexpr int PARSE_STATUS_TOO_MANY_ARGUMENTS = -5;
    } // namespace language
} // namespace mimi

#endif //STATUS_CODES_H
