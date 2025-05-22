//
// Created by dmitrydzz on 5/15/25.
//

#ifndef TESTS_H
#define TESTS_H

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

#endif //TESTS_H
