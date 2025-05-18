//
// Created by dmitrydzz on 5/15/25.
//

// ReSharper disable CppUseAuto
#ifndef TEST_MESSAGES_H
#define TEST_MESSAGES_H

#include <iostream>
#include <cstring>
#include "../source/language/string_utils.h"
#include "tests.h"
#include "message_mocks.h"

#include <string>

namespace mimi::tests::messages
{

    inline int test_hl_message_positive() {
        const char* input = "HL 10 20 30";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_OK, status, "Parse status");
        ASSERT_EQ(10, (int)message.red, "Red");
        ASSERT_EQ(20, (int)message.green, "Green");
        ASSERT_EQ(30, (int)message.blue, "Blue");

        return 0;
    }

    inline int test_hl_message_missing_args_1() {
        const char* input = " HL   ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_MISSING_ARGUMENT, status, "Parse status");

        return 0;
    }

    inline int test_hl_message_missing_args_2() {
        const char* input = " HL   10  20   ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_MISSING_ARGUMENT, status, "Parse status");

        return 0;
    }

    inline int test_hl_message_too_many_args() {
        const char* input = " HL   10  20   30  40    ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_TOO_MANY_ARGUMENTS, status, "Parse status");

        return 0;
    }

    inline int test_hl_message_wrong_arg_1() {
        const char* input = " HL   10  20.0   30    ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

        return 0;
    }

    inline int test_hl_message_wrong_arg_2() {
        const char* input = " HL   10  20   \"30\"    ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

        return 0;
    }

    inline int test_hl_message_wrong_arg_3() {
        const char* input = " HL   10  256   30    ";
        const unsigned int len = std::strlen(input);
        char lexeme[32];
        bool isString;

        const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
        ASSERT_EQ(std::string("HL"), std::string(lexeme), "Extract HL mnemonic");
        HeadlightsMockMessage message;
        const int status = message.parse(input, pos);
        ASSERT_EQ(MESSAGE_PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

        return 0;
    }

} // namespace mimi

#endif // TEST_MESSAGES_H
