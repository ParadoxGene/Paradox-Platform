#include <paradox-platform/defines.h>
#include <numerics_1_a_tests.h>
#include <numerics_1_b_tests.h>
#include <numerics_1_c_tests.h>
#include <numerics_1_d_tests.h>
#include <numerics_1_e_tests.h>
#include <unit_tests.h>
#include <stdlib.h>
#include <stdio.h>

void setUp(void)
{

}

void tearDown(void)
{

}

int main(void)
{
    paradox_bool8_t test_failures = PARADOX_FALSE;
    paradox_unit_tests_group_beg("Numerics: Numerical Text <-> Integral Type");
    paradox_platform_tests_numerics_1_a_hexadecimal_conversions();
    paradox_platform_tests_numerics_1_b_decimal_conversions();
    paradox_platform_tests_numerics_1_c_octal_conversions();
    paradox_platform_tests_numerics_1_d_ternary_conversions();
    paradox_platform_tests_numerics_1_e_binary_conversions();
    paradox_unit_tests_group_end();
    if(paradox_unit_tests_passed_all())
    {
        printf("All test cases passed.\n");
        return 0;
    }
    else
    {
        printf("Some test cases failed.\n");
        abort();
    }
}