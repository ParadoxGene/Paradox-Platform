#ifndef OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_NUMERICS
#define OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_NUMERICS

#include <paradox-platform/defines.h>

/** Numerics Error Codes. */
typedef enum paradox_numerics_errno_t
{
    PARADOX_NUMERICS_SUCCESS,
    PARADOX_NUMERICS_BAD_SIZE,
    PARADOX_NUMERICS_BAD_HEX,
    PARADOX_NUMERICS_BAD_DEC,
    PARADOX_NUMERICS_BAD_OCT,
    PARADOX_NUMERICS_BAD_TER,
    PARADOX_NUMERICS_BAD_BIN,
    PARADOX_NUMERICS_BAD_ALLOC,
    PARADOX_NUMERICS_BAD_PTR
} paradox_numerics_errno_t;

/** Converts the errno of enum paradox_numerics_errno_t to it's string literal equivalent.*/
PARADOX_PLATFORM_API paradox_str_t paradox_numerics_errno_to_string(paradox_numerics_errno_t err_code);

// *** Group 1: Numerical Text <-> Integral Type *** //

// ** Section 1.A: Hexadecimal Conversions ** //

/**
 * Converts the c-string of a nonnegative hexadecimal number to an unsigned 64-bit integer.
 * @note Conversions start from left-to-right until len amount of hex are accumulated or null character found.
 * @note Trailing 0s are not skipped.
 * @param hex the c-string of a nonnegative hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the unsigned 64-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an unsigned 64-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint64(paradox_str_t hex, const size_t len, paradox_uint64_t* codepoint);

/**
 * Converts the unsigned 64-bit integer to an allocated null-terminated c-string of a nonnegative hexadecimal number.
 * @note The allocated null-terminated c-string must be free'd when done using.
 * @param codepoint the unsigned 64-bit integer.
 * @param hex the c-string of a nonnegative hexadecimal number will be stored here.
 * @param len the length of c-string (excluding the null character) will be stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_ALLOC if allocation failed for hex parameter.
 * PARADOX_NUMERICS_PTR if hex or len parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_hex(const paradox_uint64_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a signed hexadecimal number to an signed 64-bit integer.
 * @param hex the c-string of a signed hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the signed 64-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an signed 64-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int64(paradox_str_t hex, const size_t len, paradox_int64_t* codepoint);

/**
 * Converts the signed 64-bit integer to an allocated null-terminated c-string of a signed hexadecimal number.
 * @param codepoint the signed 64-bit integer.
 * @param hex the c-string of a signed hexadecimal number will be stored here.
 * @param len the length of c-string (excluding the null character) will be stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_ALLOC if allocation failed for hex parameter.
 * PARADOX_NUMERICS_PTR if hex or len parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_hex(const paradox_int64_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a nonnegative hexadecimal number to an unsigned 32-bit integer.
 * @param hex the c-string of a nonnegative hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the unsigned 32-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an unsigned 32-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint32(paradox_str_t hex, const size_t len, paradox_uint32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_hex(const paradox_uint32_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a signed hexadecimal number to an signed 32-bit integer.
 * @param hex the c-string of a signed hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the signed 32-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an signed 32-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int32(paradox_str_t hex, const size_t len, paradox_int32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_hex(const paradox_int32_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a nonnegative hexadecimal number to an unsigned 16-bit integer.
 * @param hex the c-string of a nonnegative hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the unsigned 16-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an unsigned 16-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint16(paradox_str_t hex, const size_t len, paradox_uint16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_hex(const paradox_uint16_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a signed hexadecimal number to an signed 16-bit integer.
 * @param hex the c-string of a signed hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the signed 16-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an signed 16-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int16(paradox_str_t hex, const size_t len, paradox_int16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_hex(const paradox_int16_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a nonnegative hexadecimal number to an unsigned 8-bit integer.
 * @param hex the c-string of a nonnegative hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the unsigned 8-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an unsigned 8-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint8(paradox_str_t hex, const size_t len, paradox_uint8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_hex(const paradox_uint8_t codepoint, paradox_str_t* hex, size_t* len);

/**
 * Converts the c-string of a signed hexadecimal number to an signed 8-bit integer.
 * @param hex the c-string of a signed hexadecimal number.
 * @param len the length of the c-string (excluding the null character).
 * @param codepoint the signed 8-bit integer is stored here.
 * @returns
 * PARADOX_NUMERICS_SUCCESS on successful conversions.
 * PARADOX_NUMERICS_BAD_HEX if hex parameter is an invalid hex sequence.
 * PARADOX_NUMERICS_BAD_SIZE if len parameter is invalid value to convert to an signed 8-bit integer.
 * PARADOX_NUMERICS_BAD_PTR if the hex or codepoint parameters are null.
 */
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int8(paradox_str_t hex, const size_t len, paradox_int8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_hex(const paradox_int8_t codepoint, paradox_str_t* hex, size_t* len);

// ** Section 1.B: Decimal Conversions ** //

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint64(paradox_str_t dec, const size_t len, paradox_uint64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_dec(const paradox_uint64_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int64(paradox_str_t dec, const size_t len, paradox_int64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_dec(const paradox_int64_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint32(paradox_str_t dec, const size_t len, paradox_uint32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_dec(const paradox_uint32_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int32(paradox_str_t dec, const size_t len, paradox_int32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_dec(const paradox_int32_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint16(paradox_str_t dec, const size_t len, paradox_uint16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_dec(const paradox_uint16_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int16(paradox_str_t dec, const size_t len, paradox_int16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_dec(const paradox_int16_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint8(paradox_str_t dec, const size_t len, paradox_uint8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_dec(const paradox_uint8_t codepoint, paradox_str_t* dec, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int8(paradox_str_t dec, const size_t len, paradox_int8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_dec(const paradox_int8_t codepoint, paradox_str_t* dec, size_t* len);

// ** Section 1.C: Octal Conversions ** //

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint64(paradox_str_t oct, const size_t len, paradox_uint64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_oct(const paradox_uint64_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int64(paradox_str_t oct, const size_t len, paradox_int64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_oct(const paradox_int64_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint32(paradox_str_t oct, const size_t len, paradox_uint32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_oct(const paradox_uint32_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int32(paradox_str_t oct, const size_t len, paradox_int32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_oct(const paradox_int32_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint16(paradox_str_t oct, const size_t len, paradox_uint16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_oct(const paradox_uint16_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int16(paradox_str_t oct, const size_t len, paradox_int16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_oct(const paradox_int16_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint8(paradox_str_t oct, const size_t len, paradox_uint8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_oct(const paradox_uint8_t codepoint, paradox_str_t* oct, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int8(paradox_str_t oct, const size_t len, paradox_int8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_oct(const paradox_int8_t codepoint, paradox_str_t* oct, size_t* len);

// ** Section 1.D: Ternary Conversions ** //

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint64(paradox_str_t ter, const size_t len, paradox_uint64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_ter(const paradox_uint64_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int64(paradox_str_t ter, const size_t len, paradox_int64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_ter(const paradox_int64_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint32(paradox_str_t ter, const size_t len, paradox_uint32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_ter(const paradox_uint32_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int32(paradox_str_t ter, const size_t len, paradox_int32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_ter(const paradox_int32_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint16(paradox_str_t ter, const size_t len, paradox_uint16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_ter(const paradox_uint16_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int16(paradox_str_t ter, const size_t len, paradox_int16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_ter(const paradox_int16_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint8(paradox_str_t ter, const size_t len, paradox_uint8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_ter(const paradox_uint8_t codepoint, paradox_str_t* ter, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int8(paradox_str_t ter, const size_t len, paradox_int8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_ter(const paradox_int8_t codepoint, paradox_str_t* ter, size_t* len);

// ** Section 1.E: Binary Conversions ** //

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint64(paradox_str_t bin, const size_t len, paradox_uint64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_bin(const paradox_uint64_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int64(paradox_str_t bin, const size_t len, paradox_int64_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_bin(const paradox_int64_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint32(paradox_str_t bin, const size_t len, paradox_uint32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_bin(const paradox_uint32_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int32(paradox_str_t bin, const size_t len, paradox_int32_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_bin(const paradox_int32_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint16(paradox_str_t bin, const size_t len, paradox_uint16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_bin(const paradox_uint16_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int16(paradox_str_t bin, const size_t len, paradox_int16_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_bin(const paradox_int16_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint8(paradox_str_t bin, const size_t len, paradox_uint8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_bin(const paradox_uint8_t codepoint, paradox_str_t* bin, size_t* len);

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int8(paradox_str_t bin, const size_t len, paradox_int8_t* codepoint);
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_bin(const paradox_int8_t codepoint, paradox_str_t* bin, size_t* len);

#endif
