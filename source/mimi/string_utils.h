#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "ErrorNo.h"
#include "constants.h"

#include <cctype>
#include <cerrno>
#include <limits>
#include <type_traits>

namespace mimi
{

inline char* strclone(const char* src)
{
    if (!src) return nullptr;
    const size_t len = strlen(src);
    const auto copy = static_cast<char*>(malloc(len + 1));
    if (copy) strcpy(copy, src);
    return copy;
}

/**
 * Extracts the next whitespace-delimited word from buffer starting at startPos.
 * Skips leading whitespace, copies the word into `word`, and returns the position
 * immediately after the word. If no word is found, returns bufferLength.
 *
 * @param startPos      Index to start scanning from.
 * @param bufferLength  Total length of the input buffer.
 * @param buffer        The input string buffer.
 * @param lexeme        Output buffer to store the extracted lexeme: mnemonic or argument (must be pre-allocated).
 * @param isString      The lexeme is inside the quotation marks in the input buffer.
 * @return              Index of the next character after the extracted word, or bufferLength if
 * done.
 */
inline unsigned int extractLexeme(
    const unsigned int startPos,
    const unsigned int bufferLength, const char* buffer,
    char* lexeme, bool& isString)
{
    unsigned int pos = startPos;

    // Skip leading whitespace
    while (pos < bufferLength && std::isspace(static_cast<unsigned char>(buffer[pos])))
    {
        pos++;
    }

    if (pos >= bufferLength) {
        lexeme[0] = '\0';
        return bufferLength;
    }

    // Collect lexeme characters
    bool hasLeadingQuotationMark = false;
    bool hasEndingQuotationMark = false;
    int lexemeLength = 0;
    if (buffer[pos] == '"') // Words in quotes
    {
        hasLeadingQuotationMark = true;
        pos++; // Skip opening quotation mark
        while (pos < bufferLength) {
            if (buffer[pos] == '\\' && pos + 1 < bufferLength && buffer[pos + 1] == '"') {
                lexeme[lexemeLength++] = '"';
                pos += 2;
            } else if (buffer[pos] == '"') {
                hasEndingQuotationMark = true;
                pos++; // Closing quotation mark
                break;
            } else {
                lexeme[lexemeLength++] = buffer[pos++];
            }
        }
    }
    else // Regular word
    {
        while (pos < bufferLength && !std::isspace(static_cast<unsigned char>(buffer[pos])))
        {
            lexeme[lexemeLength++] = buffer[pos++];
        }
    }

    // Null-terminate output
    lexeme[lexemeLength] = '\0';

    isString = hasLeadingQuotationMark && hasEndingQuotationMark;

    return pos;
}

template<typename T>
typename std::enable_if<
    std::is_integral<T>::value &&
    (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8),
    T
>::type
textToLimitedInt(const char* text, const bool isString, T minValue, T maxValue, int& status)
{
    if (text[0] == '\0')
    {
        status = language::PARSE_STATUS_MISSING_ARGUMENT;
        return 0;
    }

    if (isString)
    {
        status = language::PARSE_STATUS_WRONG_ARGUMENT;
        return 0;
    }

    char* end = nullptr;
    errno = 0;

    using ParseType = typename std::conditional<
        std::is_signed<T>::value,
        long long,
        unsigned long long
    >::type;

    ParseType value = std::is_signed<T>::value
        ? static_cast<ParseType>(strtoll(text, &end, 10))
        : static_cast<ParseType>(strtoull(text, &end, 10));

    if (*end == '\0' && errno == 0 &&
        static_cast<ParseType>(minValue) <= value &&
        value <= static_cast<ParseType>(maxValue))
    {
        status = language::PARSE_STATUS_OK;
        return static_cast<T>(value);
    }

    status = language::PARSE_STATUS_WRONG_ARGUMENT;
    return 0;
}

template<typename T>
typename std::enable_if<
    std::is_unsigned<T>::value &&
    (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8),
    T
>::type
textToUint(const char* text, const bool isString, int& status)
{
    return textToLimitedInt<T>(text, isString, 0, std::numeric_limits<T>::max(), status);
}

template <typename T>
typename std::enable_if<std::is_unsigned<T>::value &&
                            (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8),
                        T>::type
textToInt(const char *text, const bool isString, int &status)
{
    return textToLimitedInt<T>(text, isString, std::numeric_limits<T>::min(),
                               std::numeric_limits<T>::max(), status);
}

inline int utoa64(uint64_t value, char* buffer)
{
    if (!buffer)
        return EINVAL;

    char tmp[21];  // max 20 digits + '\0'
    int i = 0;

    // Handle zero explicitly
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    // Convert digits in reverse order
    while (value > 0 && i < 20) {
        tmp[i++] = '0' + value % 10;
        value /= 10;
    }

    // Reverse the result into buffer
    for (int j = 0; j < i; ++j)
        buffer[j] = tmp[i - j - 1];

    buffer[i] = '\0';
    return 0;
}

} // namespace mimi

#endif // STRING_UTILS_H
