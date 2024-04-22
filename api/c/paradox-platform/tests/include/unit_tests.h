#ifndef OPEN_SOURCE_C_HEADER_PARADOX_UNIT_TESTS
#define OPEN_SOURCE_C_HEADER_PARADOX_UNIT_TESTS

#include <paradox-platform/defines.h>

#define PARADOX_UNIT_TESTS_BUF_SIZE 2048

void paradox_unit_tests_group_beg(const paradox_str_t title);
void paradox_unit_tests_group_end(void);

void paradox_unit_tests_section_beg(const paradox_str_t title);
void paradox_unit_tests_section_end(void);

void paradox_unit_tests_set_expected_and_result(paradox_str_t expected, paradox_str_t result);

void paradox_unit_test_beg(const paradox_str_t title);
void paradox_unit_test_end(void);

void paradox_unit_tests_passed(void);
void paradox_unit_tests_failed(void);

paradox_bool8_t paradox_unit_tests_passed_all(void);

#endif