#include <numerics_1_a_tests.h>
#include <paradox-platform/numerics.h>

#include <unit_tests.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*

// Unsigned Integer Macros

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
        paradox_numerics_errno_t err_code = paradox_hex_to_uint##int_sz(hex_str, (len), cp);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_BAD_"#bad_type);\
        sprintf(res_buf, "retval=%s", paradox_numerics_errno_to_string(err_code));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_BAD_##bad_type)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
    }\
    paradox_unit_test_end();
#define PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(int_sz, bad_type, cp, hex_val, len_val)\
    paradox_unit_test_beg(\
        "paradox_uint"#int_sz"_to_hex("#cp", "#hex_val", "#len_val")"\
        "=="\
        "PARADOX_NUMERICS_BAD_"#bad_type);\
    {\
        paradox_uint##int_sz##_t codepoint = (cp);\
        size_t len;\
        paradox_str_t hex = NULL;\
        paradox_numerics_errno_t err_code = paradox_uint##int_sz##_to_hex((cp), hex_val, len_val);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_BAD_"#bad_type);\
        sprintf(res_buf, "retval=%s", paradox_numerics_errno_to_string(err_code));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_BAD_##bad_type)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
        if(hex) free(hex);\
    }\
    paradox_unit_test_end();

#define PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_GOOD(int_sz, cp, hex_str, len_num)\
    paradox_unit_test_beg(\
        "paradox_uint"#int_sz"_to_hex("#cp", &hex, &len)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        "hex == "#hex_str""\
        "\n&&\n"\
        "len == "#len_num);\
    {\
        paradox_uint##int_sz##_t codepoint = (cp);\
        size_t len = 0;\
        paradox_str_t hex = NULL;\
        paradox_numerics_errno_t err_code = paradox_uint##int_sz##_to_hex((cp), &hex, &len);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_SUCCESS && hex=\"%s\" && len=%llu", (hex_str), (len_num));\
        sprintf(res_buf, "retval=%s && hex=\"%s\" && len=%llu", paradox_numerics_errno_to_string(err_code), hex, len);\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_SUCCESS && !strcmp(hex, hex_str) && len == (len_num))\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
        if(hex) free(hex);\
    }\
    paradox_unit_test_end();

#define PARADOX_UNIT_TEST_NUMERICS_INTEGRAL_TO_RADIX_STR_GOOD(sign_type, int_sz, radix_type, radix_str, radix_str_len, radix_val, radix_val_sign)\
    paradox_unit_test_beg(\
        "paradox_"#sign_type""#int_sz"_to_"#radix_type"("#radix_val", &"#radix_type", &len)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        #radix_type" == "#radix_str""\
        "\n&&\n"\
        "len == "#radix_str_len);

// Signed Integer Macros

#define PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(sign_type, int_sz, radix_type, radix_str, radix_str_len, radix_val, radix_val_sign)\
    paradox_unit_test_beg(\
        "paradox_hex_to_" #sign_type #int_sz "(\""radix_str"\", "#radix_str_len", &codepoint)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        "codepoint == "radix_str);

#define PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT_GOOD(int_sz, hex_seq, len)\
    paradox_unit_test_beg(\
        "paradox_hex_to_int"#int_sz"(\"""0x"#hex_seq"\", "#len", &codepoint)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        "codepoint == ""0x"#hex_seq);\
    {\
        paradox_int##int_sz##_t codepoint = 0x0;\
        paradox_numerics_errno_t err_code = paradox_hex_to_int##int_sz("0x"#hex_seq, (len), &codepoint);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_SUCCESS && codepoint=""0x"#hex_seq);\
        paradox_bool8_t sign = (((#hex_seq)[0] == '-') ? PARADOX_TRUE : PARADOX_FALSE);\
        if(sign) sprintf(res_buf, "retval=%s && codepoint=-0x%llX", paradox_numerics_errno_to_string(err_code), (paradox_uint64_t)(codepoint));\
        else sprintf(res_buf, "retval=%s && codepoint=0x%llX", paradox_numerics_errno_to_string(err_code), (codepoint));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_SUCCESS && codepoint == ##hex_seq)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
    }\
    paradox_unit_test_end();

#define PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT_BAD(int_sz, bad_type, hex_str, len, cp)\
    paradox_unit_test_beg(\
        "paradox_hex_to_int"#int_sz"("#hex_str", "#len", "#cp")"\
        "=="\
        "PARADOX_NUMERICS_BAD_"#bad_type);\
    {\
        paradox_int##int_sz##_t codepoint;\
        paradox_numerics_errno_t err_code = paradox_hex_to_int##int_sz(hex_str, (len), cp);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_BAD_"#bad_type);\
        sprintf(res_buf, "retval=%s", paradox_numerics_errno_to_string(err_code));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_BAD_##bad_type)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
    }\
    paradox_unit_test_end();
#define PARADOX_UNIT_TEST_NUMERICS_INT_TO_HEX_BAD(int_sz, bad_type, cp, hex_val, len_val)\
    paradox_unit_test_beg(\
        "paradox_int"#int_sz"_to_hex("#cp", "#hex_val", "#len_val")"\
        "=="\
        "PARADOX_NUMERICS_BAD_"#bad_type);\
    {\
        paradox_int##int_sz##_t codepoint = (cp);\
        size_t len;\
        paradox_str_t hex = NULL;\
        paradox_numerics_errno_t err_code = paradox_int##int_sz##_to_hex((cp), hex_val, len_val);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_BAD_"#bad_type);\
        sprintf(res_buf, "retval=%s", paradox_numerics_errno_to_string(err_code));\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_BAD_##bad_type)\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
        if(hex) free(hex);\
    }\
    paradox_unit_test_end();

#define PARADOX_UNIT_TEST_NUMERICS_INT_TO_HEX_GOOD(int_sz, cp, hex_str, len_num)\
    paradox_unit_test_beg(\
        "paradox_int"#int_sz"_to_hex("#cp", &hex, &len)"\
        "=="\
        "PARADOX_NUMERICS_SUCCESS"\
        "\n&&\n"\
        "hex == "#hex_str""\
        "\n&&\n"\
        "len == "#len_num);\
    {\
        paradox_int##int_sz##_t codepoint = (cp);\
        size_t len = 0;\
        paradox_str_t hex = NULL;\
        paradox_numerics_errno_t err_code = paradox_int##int_sz##_to_hex((cp), &hex, &len);\
        sprintf(exp_buf, "retval=PARADOX_NUMERICS_SUCCESS && hex=\"%s\" && len=%llu", (hex_str), (len_num));\
        sprintf(res_buf, "retval=%s && hex=\"%s\" && len=%llu", paradox_numerics_errno_to_string(err_code), hex, len);\
        paradox_unit_tests_set_expected_and_result(exp_buf, res_buf);\
        if(err_code == PARADOX_NUMERICS_SUCCESS && !strcmp(hex, hex_str) && len == (len_num))\
            paradox_unit_tests_passed();\
        else paradox_unit_tests_failed();\
        if(hex) free(hex);\
    }\
    paradox_unit_test_end();
*/

// Test Cases

void paradox_platform_tests_numerics_1_a_hexadecimal_conversions(void)
{
    /*
    paradox_unit_tests_section_beg("Numerics: Hexadecimal Conversion");
    {
        paradox_str_t exp_buf = malloc(PARADOX_UNIT_TESTS_BUF_SIZE*sizeof(paradox_str_char_t));
        paradox_str_t res_buf = malloc(PARADOX_UNIT_TESTS_BUF_SIZE*sizeof(paradox_str_char_t));

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, HEX, "0x1FFFFFFFFFFFFFFFF", 17, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(64, HEX, "0xFX0CL", 5,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(64, FFFF0000FFFF0000, 16);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(64, 0, 11);

        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(64, PTR, 0, NULL, &len);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(64, PTR, 0, &hex, NULL);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_GOOD(64, 0xFFFF0000FFFF0000, "FFFF0000FFFF0000", 16);
        
        PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(uint, 64, hex, "FFFF0000FFFF0000", 16, 0xFFFF0000FFFF0000, +1);
        PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(int, 64, hex, "FFFF0000FFFF000", 15, 0xFFFF0000FFFF000, +1);
        PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(int, 64, hex, "-FFFF0000FFFF000", 15, -0xFFFF0000FFFF000, -1);
        PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(uint, 64, hex, "0", 11, 0x0, +1);
        PARADOX_UNIT_TEST_NUMERICS_RADIX_STR_TO_INTEGRAL_GOOD(int, 64, hex, "0", 11, 0x0, +1);

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT_GOOD(64, FFFF0000FFFF000, 15);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT_GOOD(64, -FFFF0000FFFF000, 15);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_INT_GOOD(64, 0, 11);
        

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, HEX, "0x1FFFFFFFF", 9, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(32, HEX, "0xFX0CL", 5,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(32, FFFF0000, 8);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(32, 0, 5);

        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(32, PTR, 0, NULL, &len);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(32, PTR, 0, &hex, NULL);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_GOOD(32, 0xFFFF0000, "FFFF0000", 8);
        
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, HEX, "0x1FFFF", 5, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(16, HEX, "0xFX0", 3,&codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(16, FF00, 4);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(16, 0, 3);

        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(16, PTR, 0, NULL, &len);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(16, PTR, 0, &hex, NULL);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_GOOD(16, 0xFF00, "FF00", 4);

        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, HEX, "0x1FF", 3, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, SIZE, "", 0, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, PTR, NULL, 1, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, PTR, "0xF", 1, NULL);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_BAD(8, HEX, "0xFX", 2, &codepoint);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(8, F0, 2);
        PARADOX_UNIT_TEST_NUMERICS_HEX_TO_UINT_GOOD(8, 0, 2);

        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(8, PTR, 0, NULL, &len);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_BAD(8, PTR, 0, &hex, NULL);
        PARADOX_UNIT_TEST_NUMERICS_UINT_TO_HEX_GOOD(8, 0xF0, "F0", 2);
        
        free(res_buf);
        free(exp_buf);
    }
    paradox_unit_tests_section_end();    
    */
}