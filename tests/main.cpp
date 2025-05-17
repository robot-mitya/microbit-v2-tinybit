//
// Created by dmitrydzz on 5/15/25.
//

#include "test_string_utils.h"
#include "test_messages.h"

int main() {
    int result = 0;
    result |= test_basic_extraction();
    result |= test_leading_spaces();
    result |= test_only_spaces();
    result |= test_quoted_argument();
    result |= test_broken_quoted_argument();
    result |= test_escaped_quote_inside_string();
    result |= test_one_escaped_quote_inside_string();

    result |= test_hl_message_positive();
    result |= test_hl_message_missing_args_1();
    result |= test_hl_message_missing_args_2();
    result |= test_hl_message_too_many_args();
    result |= test_hl_message_wrong_arg_1();
    result |= test_hl_message_wrong_arg_2();
    result |= test_hl_message_wrong_arg_3();

    if (result == 0) {
        std::cout << COLOR_GREEN << "\nAll tests passed!\n" << COLOR_RESET << std::endl;
    } else {
        std::cout << COLOR_RED << "\nSome tests failed!" << COLOR_RESET << std::endl;
    }

    // int status;
    // uint8_t value = Message::textToUint8("\"30\"", status);
    // std::cout << "value: " << (int)value << std::endl;
    // std::cout << "status: " << status << std::endl;

    return result;
}
