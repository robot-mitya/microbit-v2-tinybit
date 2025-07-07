// ReSharper disable CppUseAuto
#ifndef TEST_DISTANCE_REQUEST_MESSAGES_H
#define TEST_DISTANCE_REQUEST_MESSAGES_H

#include <iostream>
#include <cstring>
#include "../source/mimi/string_utils.h"
#include "tests.h"
#include "dummy_mocks.h"
#include "message_mocks.h"

#include <string>

namespace mimi::tests::messages
{

inline int test_dist_req_message_positive() {
    const char* input = "dist? 100";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_OK, status, "Parse status");
    ASSERT_EQ(100, (int)message.periodMillis, "periodMillis");

    return 0;
}

inline int test_dist_req_message_missing_all_args() {
    const char* input = " dist?   ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_OK, status, "Parse status");
    ASSERT_EQ(0, (int)message.periodMillis, "periodMillis");

    return 0;
}

inline int test_dist_req_message_too_many_args() {
    const char* input = " dist?   10  20   30  40    ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_OK, status, "Parse status");
    ASSERT_EQ(10, (int)message.periodMillis, "periodMillis");

    return 0;
}

inline int test_dist_req_message_wrong_arg_1() {
    const char* input = " dist?   10.0    ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

    return 0;
}

inline int test_dist_req_message_wrong_arg_2() {
    const char* input = " dist?   \"30\"    ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

    return 0;
}

inline int test_dist_req_message_wrong_arg_3() {
    const char* input = " dist?   -10    ";
    const unsigned int len = std::strlen(input);
    char lexeme[32];
    bool isString;

    const unsigned int pos = extractLexeme(0, len, input, lexeme, isString);
    ASSERT_EQ(std::string("dist?"), std::string(lexeme), "Extract dist? mnemonic");
    DummyCore dummyCore;
    DistanceRequestMockMessage message(dummyCore);
    const int status = message.parse(input, pos);
    ASSERT_EQ(mimi::language::PARSE_STATUS_WRONG_ARGUMENT, status, "Parse status");

    return 0;
}

} // namespace mimi::tests::messages

#endif //TEST_DISTANCE_REQUEST_MESSAGES_H
