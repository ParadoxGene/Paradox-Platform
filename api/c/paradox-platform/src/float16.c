#include <paradox-platform/float16.h>

PARADOX_PLATFORM_API paradox_str_t paradox_float16_errno_to_string(paradox_float16_errno_t err_code)
{
    switch(err_code)
    {
        case PARADOX_FLOAT16_SUCCESS: return "PARADOX_FLOAT16_SUCCESS";
        default: return "";
    }
}

PARADOX_PLATFORM_API paradox_float32_t paradox_float16_to_float32(const paradox_float16_t value)
{
    paradox_float32_t offset;
    if(0 == value.exp)
    {
        if(0 == value.frac) return 0.0f;
        else offset = 0.0f;
    }
    else offset = 1.0f;
    
    paradox_int8_t sign_val = (value.sign ? -1 : 1);
    paradox_float32_t exp_val;
    switch(value.exp - paradox_float16_bias)
    {
    case  15: exp_val = 32768.0f; break;
    case  14: exp_val = 16384.0f; break;
    case  13: exp_val = 8192.0f; break;
    case  12: exp_val = 4096.0f; break;
    case  11: exp_val = 2048.0f; break;
    case  10: exp_val = 1024.0f; break;
    case   9: exp_val = 512.0f; break;
    case   8: exp_val = 256.0f; break;
    case   7: exp_val = 128.0f; break;
    case   6: exp_val = 64.0f; break;
    case   5: exp_val = 32.0f; break;
    case   4: exp_val = 16.0f; break;
    case   3: exp_val = 8.0f; break;
    case   2: exp_val = 4.0f; break;
    case   1: exp_val = 2.0f; break;
    case   0: exp_val = 1.0f; break;
    case  -1: exp_val = 0.5f; break;
    case  -2: exp_val = 0.25f; break;
    case  -3: exp_val = 0.125f; break;
    case  -4: exp_val = 0.0625f; break;
    case  -5: exp_val = 0.03125f; break;
    case  -6: exp_val = 0.015625f; break;
    case  -7: exp_val = 0.0078125f; break;
    case  -8: exp_val = 0.00390625f; break;
    case  -9: exp_val = 0.001953125f; break;
    case -10: exp_val = 0.0009765625f; break;
    case -11: exp_val = 0.00048828125f; break;
    case -12: exp_val = 0.000244140625f; break;
    case -13: exp_val = 0.0001220703125f; break;
    case -14: exp_val = 0.00006103515625; break;
    case -15: exp_val = 0.00006103515625; break;
    }

    paradox_float32_t frac_val = offset
        + 0.5f * ((value.frac & 1 << 9) ? 1 : 0)
        + 0.25f * ((value.frac & 1 << 8) ? 1 : 0)
        + 0.125f * ((value.frac & 1 << 7) ? 1 : 0)
        + 0.0625f * ((value.frac & 1 << 6) ? 1 : 0)
        + 0.03125f * ((value.frac & 1 << 5) ? 1 : 0)
        + 0.015625f * ((value.frac & 1 << 4) ? 1 : 0)
        + 0.0078125f * ((value.frac & 1 << 3) ? 1 : 0)
        + 0.00390625f * ((value.frac & 1 << 2) ? 1 : 0)
        + 0.001953125f * ((value.frac & 1 << 1) ? 1 : 0)
        + 0.0009765625f * ((value.frac & 1 << 0) ? 1 : 0);

    return sign_val * exp_val * frac_val;
}
PARADOX_PLATFORM_API paradox_float16_t paradox_float32_to_float16(const paradox_float32_t value)
{

}
PARADOX_PLATFORM_API paradox_float64_t paradox_float16_to_float64(const paradox_float16_t value)
{
    return paradox_float16_to_float32(value);
}
PARADOX_PLATFORM_API paradox_float16_t paradox_float64_to_float16(const paradox_float64_t value)
{

}

PARADOX_PLATFORM_API paradox_float16_t paradox_add_float16(const paradox_float16_t operand1, const paradox_float16_t operand2)
{
    paradox_float16_t sum;
    
    // step 1: set sign

    if(operand1.sign == operand2.sign) sum.sign = operand1.sign;

    // step 2: prepend 1 in the mantissas
    
    paradox_uint64_t frac1 = operand1.frac | (operand1.exp ? (1 << 10) : 0);
    paradox_uint64_t frac2 = operand2.frac | (operand2.exp ? (1 << 10) : 0);

    // step 3: shift binary point

    paradox_uint8_t dist;
    if(operand1.exp > operand2.exp)
    {
        dist = operand1.exp - operand2.exp;
        frac1 <<= dist;
        sum.exp = operand1.exp;
    }
    else if(operand2.exp > operand1.exp)
    {
        dist = operand2.exp - operand1.exp;
        frac2 <<= dist;
        sum.exp = operand2.exp;
    }
    else dist = 0;

    // step 4: add mantissas

    frac1 += frac2;

    // step 5: normalization

    if(frac1 >= (1 << (dist + 11)))
    {
        sum.exp += 1;
        dist += 1;
    }

    // step 6: rounding mode: nearest

    paradox_uint8_t round_bit = frac1 & (1 << dist);
    paradox_uint8_t next_bit = frac1 & (1 << (dist - 1));
    if(next_bit) // check what follows round bit is a 1.
    {
        if(round_bit || ((frac1 & ((1 << dist) - 1)) > (1 << (dist - 1))))
        {   // if round bit is 1, round up
            // or check if following bits after round bit contains another 1.
            frac1 >>= dist;
            frac1 += 1;
        }
    }
    else frac1 >>= dist;
    sum.frac = frac1 & 1023;
    return sum;
}
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_add_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result)
{

}

PARADOX_PLATFORM_API paradox_float16_t paradox_sub_float16(const paradox_float16_t operand1, const paradox_float16_t operand2)
{

}
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_sub_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result)
{

}

PARADOX_PLATFORM_API paradox_float16_t paradox_mul_float16(const paradox_float16_t operand1, const paradox_float16_t operand2)
{

}
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_mul_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result)
{

}

PARADOX_PLATFORM_API paradox_float16_t paradox_div_float16(const paradox_float16_t operand1, const paradox_float16_t operand2)
{

}
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_div_float16_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_float16_t* result)
{

}

PARADOX_PLATFORM_API paradox_int8_t paradox_float16_compare(const paradox_float16_t operand1, const paradox_float16_t operand2)
{

}
PARADOX_PLATFORM_API paradox_float16_errno_t paradox_float16_compare_s(const paradox_float16_t operand1, const paradox_float16_t operand2, paradox_int8_t* result)
{

}
