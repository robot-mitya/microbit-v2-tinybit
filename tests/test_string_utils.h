// ReSharper disable CppUseAuto
#ifndef TEST_STRING_UTILS_H
#define TEST_STRING_UTILS_H

#include <iostream>
#include <cstring>
#include "../source/language/string_utils.h"
#include "tests.h"

inline int test_basic_extraction() {
    const char* input = "MOVE 10 20";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("MOVE"), std::string(lexeme), "Extract mnemonic");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("10"), std::string(lexeme), "Extract arg1");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("20"), std::string(lexeme), "Extract arg2");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string(""), std::string(lexeme), "No more lexemes");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_leading_spaces() {
    const char* input = "  \t\t  TEMP  \t\t  36.6";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("TEMP"), std::string(lexeme), "Skip leading spaces and tabs");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("36.6"), std::string(lexeme), "Extract second lexeme with leading spaces and tabs");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_only_spaces() {
    const char* input = "    \t \t ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string(""), std::string(lexeme), "No lexemes found");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_quoted_argument() {
    const char* input = "SAY \"Hello World\" 123";
    const unsigned int len = std::strlen(input);
    char lexeme[64];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("SAY"), std::string(lexeme), "Mnemonic SAY");
    ASSERT_EQ(false, isString, "Mnemonic is not string");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("Hello World"), std::string(lexeme), "Quoted string");
    ASSERT_EQ(true, isString, "Quoted string is string");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("123"), std::string(lexeme), "Numeric arg");
    ASSERT_EQ(false, isString, "Numeric arg is not string");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_broken_quoted_argument() {
    const char* input = "SAY \"Hello World 123";
    const unsigned int len = std::strlen(input);
    char lexeme[64];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("SAY"), std::string(lexeme), "Mnemonic SAY");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("Hello World 123"), std::string(lexeme), "Broken quoted string");
    ASSERT_EQ(false, isString, "Broken quoted string is not string");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_escaped_quote_inside_string() {
    const char* input = R"(MSG "She said: \"yes\"")";
    const unsigned int len = std::strlen(input);
    char lexeme[64];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("MSG"), std::string(lexeme), "Mnemonic MSG");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("She said: \"yes\""), std::string(lexeme), "Escaped quote inside string");
    ASSERT_EQ(true, isString, "String is a string");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

inline int test_one_escaped_quote_inside_string() {
    const char* input = R"(MSG "She said: \"yes")";
    const unsigned int len = std::strlen(input);
    char lexeme[64];
    bool isString;

    unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("MSG"), std::string(lexeme), "Mnemonic MSG");

    pos = extractLexeme(pos, len, input, lexeme, isString);
    ASSERT_EQ(std::string("She said: \"yes"), std::string(lexeme), "Escaped quote inside string");
    ASSERT_EQ(true, isString, "String is a string");
    ASSERT_EQ(len, pos, "Position at the end");

    return 0;
}

#endif // TEST_STRING_UTILS_H
