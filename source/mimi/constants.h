#ifndef STATUS_CODES_H
#define STATUS_CODES_H

namespace mimi
{
    namespace language
    {
        constexpr int PARSE_STATUS_OK = 0;
        constexpr int PARSE_STATUS_MISSING_ARGUMENT = -1;
        constexpr int PARSE_STATUS_WRONG_ARGUMENT = -2;
        constexpr int PARSE_STATUS_TOO_MANY_ARGUMENTS = -3;
    } // namespace language
} // namespace mimi

#endif //STATUS_CODES_H
