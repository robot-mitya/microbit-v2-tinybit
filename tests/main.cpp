//
// Created by dmitrydzz on 5/15/25.
//

#include "test_string_utils.h"
#include "test_headlight_messages.h"
#include "test_drive_motors_messages.h"
#include "test_message_queue.h"
#include "test_language_controller.h"

using namespace mimi::tests;

int main() {
    int result = 0;
    result |= string_utils::test_basic_extraction();
    result |= string_utils::test_leading_spaces();
    result |= string_utils::test_only_spaces();
    result |= string_utils::test_quoted_argument();
    result |= string_utils::test_broken_quoted_argument();
    result |= string_utils::test_escaped_quote_inside_string();
    result |= string_utils::test_one_escaped_quote_inside_string();

    result |= messages::test_hl_message_positive();
    result |= messages::test_hl_message_missing_all_args();
    result |= messages::test_hl_message_missing_second_arg();
    result |= messages::test_hl_message_too_many_args();
    result |= messages::test_hl_message_wrong_arg_1();
    result |= messages::test_hl_message_wrong_arg_2();
    result |= messages::test_hl_message_wrong_arg_3();

    result |= messages::test_drv_message_positive();
    result |= messages::test_drv_message_missing_all_args();
    result |= messages::test_drv_message_missing_second_arg();
    result |= messages::test_drv_message_too_many_args();
    result |= messages::test_drv_message_wrong_arg_1();
    result |= messages::test_drv_message_wrong_arg_2();
    result |= messages::test_drv_message_wrong_arg_3();

    result |= message_queue::test_message_queue_basic_positive();
    result |= message_queue::test_message_queue_enqueue_scenarios();
    result |= message_queue::test_message_queue_dequeue_scenarios();

    result |= language_controller::test_uninitialized_command_processor();
    result |= language_controller::test_command_processor_on_nonexisting_mnemonic();
    result |= language_controller::test_command_processor_positive_scenarios();

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
