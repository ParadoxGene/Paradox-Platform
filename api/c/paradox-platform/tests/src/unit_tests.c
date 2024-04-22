#include <unit_tests.h>
#include <paradox-platform/console.h>

#include <stdio.h>

paradox_bool8_t unit_test_failed = PARADOX_FALSE;

paradox_str_t unit_test_case_title;
paradox_str_t unit_test_case_expected;
paradox_str_t unit_test_case_result;

paradox_str_t    unit_test_group_title;
paradox_uint64_t unit_test_group_total_cases_count;
paradox_uint64_t unit_test_group_passed_cases_count;

paradox_str_t    unit_test_section_title;
paradox_uint64_t unit_test_section_total_cases_count;
paradox_uint64_t unit_test_section_passed_cases_count;

void paradox_unit_tests_group_beg(const paradox_str_t title)
{
    printf("===========================\n");
    printf(PARADOX_CONSOLE_COLOR_YELLOW "Test Group [BEGIN]: " PARADOX_CONSOLE_COLOR_RESET);
    unit_test_group_title = title;
    unit_test_group_total_cases_count = 0;
    unit_test_group_passed_cases_count = 0;
    printf(unit_test_group_title);
    printf("\n");
}
void paradox_unit_tests_group_end(void)
{
    printf(PARADOX_CONSOLE_COLOR_YELLOW "\nTest Group [RESULTS]: " PARADOX_CONSOLE_COLOR_RESET);
    printf(unit_test_group_title);
    printf(PARADOX_CONSOLE_COLOR_YELLOW "\nTest Group Passed/Total: %llu/%llu\n" PARADOX_CONSOLE_COLOR_RESET, unit_test_group_passed_cases_count, unit_test_group_total_cases_count);
    printf("===========================\n\n");
}

void paradox_unit_tests_section_beg(const paradox_str_t title)
{
    printf("---------------------------\n");
    printf(PARADOX_CONSOLE_COLOR_YELLOW "Test Section [BEGIN]: " PARADOX_CONSOLE_COLOR_RESET);
    unit_test_section_title = title;
    unit_test_section_total_cases_count = 0;
    unit_test_section_passed_cases_count = 0;
    printf(unit_test_section_title);
    printf("\n");
}
void paradox_unit_tests_section_end(void)
{
    printf(PARADOX_CONSOLE_COLOR_YELLOW "\nTest Section [RESULTS]: " PARADOX_CONSOLE_COLOR_RESET);
    printf(unit_test_section_title);
    printf(PARADOX_CONSOLE_COLOR_YELLOW "\nTest Section Passed/Total: %llu/%llu\n" PARADOX_CONSOLE_COLOR_RESET, unit_test_section_passed_cases_count, unit_test_section_total_cases_count);
    printf("---------------------------\n");
}

void paradox_unit_tests_set_expected_and_result(paradox_str_t expected, paradox_str_t result)
{
    unit_test_case_expected = expected;
    unit_test_case_result = result;
}

void paradox_unit_test_beg(const paradox_str_t title)
{
    unit_test_case_title = title;

    printf("***************************\n");
    printf(PARADOX_CONSOLE_COLOR_YELLOW "Starting Test...\n" PARADOX_CONSOLE_COLOR_RESET "%s\n", unit_test_case_title);
}
void paradox_unit_test_end(void)
{
    printf("***************************\n");
}

void paradox_unit_tests_passed(void)
{
    unit_test_group_passed_cases_count += 1;
    unit_test_group_total_cases_count += 1;
    unit_test_section_passed_cases_count += 1;
    unit_test_section_total_cases_count += 1;
    printf(PARADOX_CONSOLE_COLOR_GREEN "Test Passed!\n" PARADOX_CONSOLE_COLOR_RESET);
}
void paradox_unit_tests_failed(void)
{
    unit_test_group_total_cases_count += 1;
    unit_test_section_total_cases_count += 1;
    unit_test_failed = PARADOX_TRUE;
    printf(PARADOX_CONSOLE_COLOR_RED "Test Failed.\n" PARADOX_CONSOLE_COLOR_RESET
        "Expected:\n" PARADOX_CONSOLE_COLOR_CYAN "%s\n" PARADOX_CONSOLE_COLOR_RESET
        "Result:\n" PARADOX_CONSOLE_COLOR_RED "%s\n" PARADOX_CONSOLE_COLOR_RESET,
        unit_test_case_expected, unit_test_case_result);
}

paradox_bool8_t paradox_unit_tests_passed_all(void)
{
    return !unit_test_failed;
}