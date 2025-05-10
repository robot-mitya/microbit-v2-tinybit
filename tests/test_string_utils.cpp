#include <iostream>
#include <cstring>
#include "../source/language/string_utils.h"

#define USE_COLORS 1

#if USE_COLORS
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED   "\033[1;31m"
#define COLOR_RESET "\033[0m"
#else
#define COLOR_GREEN ""
#define COLOR_RED   ""
#define COLOR_RESET ""
#endif

#define ASSERT_EQ(expected, actual, description) \
do { \
std::cout << __func__ << "(): "; \
if ((expected) != (actual)) { \
std::cout << COLOR_RED << description << " [FAIL]" << COLOR_RESET \
<< ": expected " << (expected) << ", got " << (actual) \
<< std::endl; \
return 1; \
} else { \
std::cout << COLOR_GREEN << description << " [OK]" << COLOR_RESET \
<< std::endl; \
} \
} while (0)

int test_basic_extraction() {
    const char* input = "MOVE 10 20";
    const unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("MOVE"), std::string(word), "Extract mnemonic");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("10"), std::string(word), "Extract arg1");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("20"), std::string(word), "Extract arg2");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string(""), std::string(word), "No more words");

    return 0;
}

int test_leading_spaces() {
    const char* input = "  \t\t  TEMP  \t\t  36.6";
    const unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("TEMP"), std::string(word), "Skip leading spaces and tabs");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("36.6"), std::string(word), "Extract second word with leading spaces and tabs");

    return 0;
}

int test_only_spaces() {
    const char* input = "    \t \t ";
    const unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string(""), std::string(word), "No words found");
    ASSERT_EQ(len, pos, "Position at end");

    return 0;
}

int test_quoted_argument() {
    const char* input = "SAY \"Hello World\" 123";
    const unsigned int len = std::strlen(input);
    char word[64];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("SAY"), std::string(word), "mnemonic SAY");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("Hello World"), std::string(word), "quoted string");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("123"), std::string(word), "numeric arg");

    return 0;
}

int test_broken_quoted_argument() {
    const char* input = "SAY \"Hello World 123";
    const unsigned int len = std::strlen(input);
    char word[64];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("SAY"), std::string(word), "mnemonic SAY");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("Hello World 123"), std::string(word), "broken quoted string");

    return 0;
}

int test_escaped_quote_inside_string() {
    const char* input = R"(MSG "He said: \"yes\"")";
    const unsigned int len = std::strlen(input);
    char word[64];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("MSG"), std::string(word), "mnemonic MSG");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("He said: \"yes\""), std::string(word), "escaped quote inside string");

    return 0;
}

int main() {
    int result = 0;
    result |= test_basic_extraction();
    result |= test_leading_spaces();
    result |= test_only_spaces();
    result |= test_quoted_argument();
    result |= test_broken_quoted_argument();
    result |= test_escaped_quote_inside_string();

    if (result == 0) {
        std::cout << COLOR_GREEN << "\nAll tests passed!\n" << COLOR_RESET << std::endl;
    } else {
        std::cout << COLOR_RED << "\nSome tests failed!" << COLOR_RESET << std::endl;
    }

    return result;
}
