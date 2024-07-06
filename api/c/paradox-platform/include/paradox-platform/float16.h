#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_FLOAT16_T
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_FLOAT16_T

#include <paradox-platform/defines.h>

/** 16-bit Floating Point Error Codes. */
typedef enum paradox_float16_errno_t
{
    PARADOX_FLOAT16_SUCCESS,
    PARADOX_FLOAT16_NAN
} paradox_float16_errno_t;

/** Converts the errno of enum paradox_float16_errno_t to it's string literal equivalent.*/
PARADOX_PLATFORM_API paradox_str_t paradox_float16_errno_to_string(paradox_float16_errno_t err_code);

typedef struct paradox_float16_t
{
    paradox_uint16_t frac: 10;
    paradox_uint8_t  exp:  5;
    paradox_uint8_t  sign: 1;
} paradox_float16_t;

const paradox_float16_t paradox_float16_pos_inf = {0, 0x1F, 0};
const paradox_float16_t paradox_float16_neg_inf = {0, 0x1F, 1};
const paradox_int8_t   paradox_float16_bias = 15;

PARADOX_PLATFORM_API paradox_float32_t paradox_float16_to_float32(const paradox_float16_t value);
PARADOX_PLATFORM_API paradox_float16_t paradox_float32_to_float16(const paradox_float32_t value);
PARADOX_PLATFORM_API paradox_float64_t paradox_float16_to_float64(const paradox_float16_t value);
PARADOX_PLATFORM_API paradox_float16_t paradox_float64_to_float16(const paradox_float64_t value);

PARADOX_PLATFORM_API paradox_float16_t paradox_add_float16(const paradox_float16_t operand1, const paradox_float16_t operand2);
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_add_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result);

PARADOX_PLATFORM_API paradox_float16_t paradox_sub_float16(const paradox_float16_t operand1, const paradox_float16_t operand2);
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_sub_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result);

PARADOX_PLATFORM_API paradox_float16_t paradox_mul_float16(const paradox_float16_t operand1, const paradox_float16_t operand2);
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_mul_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result);

PARADOX_PLATFORM_API paradox_float16_t paradox_div_float16(const paradox_float16_t operand1, const paradox_float16_t operand2);
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_div_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result);

PARADOX_PLATFORM_API paradox_int8_t paradox_float16_compare(const paradox_float16_t operand1, const paradox_float16_t operand2);
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_float16_compare_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_int8_t* result);

PARADOX_PLATFORM_API paradox_bool8_t paradox_float16_is_nan(const paradox_float16_t value);
PARADOX_PLATFORM_API paradox_bool8_t paradox_float16_is_inf(const paradox_float16_t value);
#endif