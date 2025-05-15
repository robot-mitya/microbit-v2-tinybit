#ifndef TEST_STRING_UTILS_H
#define TEST_STRING_UTILS_H

#include <iostream>
#include <cstring>
#include "../source/language/string_utils.h"
#include "tests.h"

inline int test_basic_extraction() {
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

inline int test_leading_spaces() {
    const char* input = "  \t\t  TEMP  \t\t  36.6";
    const unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("TEMP"), std::string(word), "Skip leading spaces and tabs");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("36.6"), std::string(word), "Extract second word with leading spaces and tabs");

    return 0;
}

inline int test_only_spaces() {
    const char* input = "    \t \t ";
    const unsigned int len = std::strlen(input);
    char word[32];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string(""), std::string(word), "No words found");
    ASSERT_EQ(len, pos, "Position at end");

    return 0;
}

inline int test_quoted_argument() {
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

inline int test_broken_quoted_argument() {
    const char* input = "SAY \"Hello World 123";
    const unsigned int len = std::strlen(input);
    char word[64];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("SAY"), std::string(word), "mnemonic SAY");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("Hello World 123"), std::string(word), "broken quoted string");

    return 0;
}

inline int test_escaped_quote_inside_string() {
    const char* input = R"(MSG "He said: \"yes\"")";
    const unsigned int len = std::strlen(input);
    char word[64];

    unsigned int pos = extractWord(0, len, input, word);
    ASSERT_EQ(std::string("MSG"), std::string(word), "mnemonic MSG");

    pos = extractWord(pos, len, input, word);
    ASSERT_EQ(std::string("He said: \"yes\""), std::string(word), "escaped quote inside string");

    return 0;
}

#endif // TEST_STRING_UTILS_H
