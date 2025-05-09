#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cctype>

/**
 * Extracts the next whitespace-delimited word from buffer starting at startPos.
 * Skips leading whitespace, copies the word into `word`, and returns the position
 * immediately after the word. If no word is found, returns bufferLength.
 *
 * @param startPos      Index to start scanning from.
 * @param bufferLength  Total length of the input buffer.
 * @param buffer        The input string buffer.
 * @param word          Output buffer to store the extracted word (must be pre-allocated).
 * @return              Index of the next character after the extracted word, or bufferLength if
 * done.
 */
inline unsigned int extractWord(
    const unsigned int startPos, const unsigned int bufferLength, const char* buffer, char* word)
{
    unsigned int pos = startPos;

    // Skip leading whitespace
    while (pos < bufferLength && std::isspace(static_cast<unsigned char>(buffer[pos])))
    {
        pos++;
    }

    if (pos >= bufferLength) {
        word[0] = '\0';
        return bufferLength;
    }

    // Collect word characters
    int wordLength = 0;
    if (buffer[pos] == '"') // Words in quotes
    {
        pos++; // Skip opening quotation mark
        while (pos < bufferLength) {
            if (buffer[pos] == '\\' && pos + 1 < bufferLength && buffer[pos + 1] == '"') {
                word[wordLength++] = '"';
                pos += 2;
            } else if (buffer[pos] == '"') {
                pos++; // Closing quotation mark
                break;
            } else {
                word[wordLength++] = buffer[pos++];
            }
        }
    }
    else // Regular word
    {
        while (pos < bufferLength && !std::isspace(static_cast<unsigned char>(buffer[pos])))
        {
            word[wordLength++] = buffer[pos++];
        }
    }

    // Null-terminate output
    word[wordLength] = '\0';

    return pos;
}

#endif // STRING_UTILS_H
