#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "constants.h"

#include <cctype>
#include <cinttypes>
#include <cerrno>
#include <cstdlib>

namespace mimi
{

inline char* strclone(const char* src)
{
    if (!src) return nullptr;
    const size_t len = strlen(src);
    auto copy = static_cast<char*>(malloc(len + 1));
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

inline uint8_t textToUint8(const char* text, const bool isString, int& status)
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
    char *end = nullptr;
    errno = 0;
    const unsigned long value = strtoul(text, &end, 10);
    if (*end == '\0' && value <= 255 && errno == 0)
    {
        status = language::PARSE_STATUS_OK;
        return static_cast<uint8_t>(value);
    }
    status = language::PARSE_STATUS_WRONG_ARGUMENT;
    return 0;
}

inline long textToLong(const char* text, const bool isString, long minValue, long maxValue, int& status)
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
    char *end = nullptr;
    errno = 0;
    const long value = strtol(text, &end, 10);
    if (*end == '\0' && value >= minValue && value <= maxValue && errno == 0)
    {
        status = language::PARSE_STATUS_OK;
        return value;
    }
    status = language::PARSE_STATUS_WRONG_ARGUMENT;
    return 0;
}

} // namespace mimi

#endif // STRING_UTILS_H
