#include <numerics_1_a_tests.h>
#include <paradox-platform/numerics.h>

#include <unit_tests.h>
#include <stdlib.h>
#include <stdio.h>

#define PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(int_sz, hex_seq, len)\
    paradox_unit_test_beg(\
        "paradox_hex_to_uint"#int_sz"(\"""0x"#hex_seq"\", "#len", &codepoint)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        "codepoint == ""0x"#hex_seq);\
    {\
        paradox_uint##int_sz##_t codepoint = 0x0;\
        paradox_numerics_errno_t err_code = paradox_hex_to_uint##int_sz("0x"#hex_seq, (len), &codepoint);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_SUCCESS && codepoint=""0x"#hex_seq);\
        sprintf(res_buf, "retval=%s && codepoint=0x%llX", paradox_numerics_errno_to_string(err_code), codepoint);\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_SUCCESS && codepoint == 0x##hex_seq)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
    }\
    paradox_unit_test_end();

#define PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(int_sz, bad_type, hex_str, len, cp)\
    paradox_unit_test_beg(\
        "paradox_hex_to_uint"#int_sz"("#hex_str", "#len", "#cp")"\
        "=="\
        "PARADOX_NUMERICS_BAD_"#bad_type);\
    {\
        paradox_uint##int_sz##_t codepoint;\
        paradox_numerics_errno_t err_code = paradox_hex_to_uint##int_sz(##hex_str, (len), ##cp);\
        sprintf(exp_buf, "retval = PARADOX_NUMERICS_BAD_"#bad_type);\
        sprintf(res_buf, "retval = %s", paradox_numerics_errno_to_string(err_code));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_BAD_##bad_type)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
    }\
    paradox_unit_test_end();
#define PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT()

void paradox_platform_tests_numerics_1_a_hexadecimal_conversions(void)
{
    paradox_unit_tests_section_beg("Numerics: Hexadecimal Conversion");
    {
        paradox_str_t exp_buf = malloc(PARADOX_UNIT_TESTS_BUF_SIZE*sizeof(paradox_str_char_t));
        paradox_str_t res_buf = malloc(PARADOX_UNIT_TESTS_BUF_SIZE*sizeof(paradox_str_char_t));

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, SIZE, "0x1FFFFFFFFFFFFFFFF", 17, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, SIZE, "", 5, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, HEX, "0xFX0CL", 5,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(64, FFFF0000FFFF0000, 16);

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, SIZE, "0x1FFFFFFFF", 9, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, SIZE, "", 5, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, HEX, "0xFX0CL", 5,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(32, FFFF0000, 8);

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, SIZE, "0x1FFFF", 5, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, SIZE, "", 3, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, HEX, "0xFX0", 3,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(16, FF00, 4);

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, SIZE, "0x1FF", 3, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, SIZE, "", 2, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, HEX, "0xFX", 2, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(8, F0, 2);
        
        free(res_buf);
        free(exp_buf);
    }
    paradox_unit_tests_section_end();

    
}