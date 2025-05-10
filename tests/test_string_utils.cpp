#include <iostream>
#include <cstring>
#include "../source/language/string_utils.h"

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED   "\033[1;31m"
#define COLOR_RESET "\033[0m"

#define ASSERT_EQ(expected, actual, message) \
if ((expected) != (actual)) { \
std::cerr << COLOR_RED << "FAIL: " << message \
<< ": expected " << (expected) \
<< ", got " << (actual) << COLOR_RESET << std::endl; \
return 1; \
} else { \
std::cout << COLOR_GREEN << message << " passed" << COLOR_RESET \
<< std::endl; \
}

int test_basic_extraction() {
    const char* input = "MOVE 10 20";
    unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("MOVE"), std::string(word), "Test 1: mnemonic");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("10"), std::string(word), "Test 2: arg1");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("20"), std::string(word), "Test 3: arg2");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string(""), std::string(word), "Test 4: no more words");

    return 0;
}

int test_leading_spaces() {
    const char* input = "   TEMP 36.6";
    unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("TEMP"), std::string(word), "Test 5: skip leading spaces");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("36.6"), std::string(word), "Test 6: second word");

    return 0;
}

int test_only_spaces() {
    const char* input = "    \t \t ";
    unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string(""), std::string(word), "Test 7: no words found");
    ASSERT_EQ(len, pos, "Test 8: position at end");

    return 0;
}

int main() {
    int result = 0;
    result |= test_basic_extraction();
    result |= test_leading_spaces();
    result |= test_only_spaces();

    if (result == 0) {
        std::cout << "\nAll tests passed!\n" << std::endl;
    }
    return result;
}
