#include "sha2_utils.h"

/**
 * Rotate bits of a 32-bit unsigned integer to the left.
 *
 * @param a The integer to rotate.
 * @param b The number of bits to rotate by.
 * @return The rotated integer.
 */
uint32_t rotl32(uint32_t a, uint32_t b) {
    return (a << b) | (a >> (32 - b));
}

/**
 * Rotate bits of a 32-bit unsigned integer to the right.
 *
 * @param a The integer to rotate.
 * @param b The number of bits to rotate by.
 * @return The rotated integer.
 */
uint32_t rotr32(uint32_t a, uint32_t b) {
    return (a >> b) | (a << (32 - b));
}

/**
 * Choose function used in SHA-256.
 * For each bit position in the output, the bit is taken from x if the
 * corresponding bit of y is 1 and from z if the corresponding bit of y is 0.
 *
 * @param x The first input integer.
 * @param y The second input integer, acting as a chooser between x and z.
 * @param z The third input integer.
 * @return The result of the choose operation.
 */
uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

/**
 * Majority function used in SHA-256.
 * For each bit position in the output, the bit is taken from the majority
 * of the corresponding bits of the three inputs.
 *
 * @param x The first input integer.
 * @param y The second input integer.
 * @param z The third input integer.
 * @return The result of the majority operation.
 */
uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

/**
 * Sigma0 function used in SHA-256.
 * This is used in the message schedule computation (expanding the message
 * block into sixty-four 32-bit words).
 *
 * @param x The input integer.
 * @return The result of the Sigma0 operation.
 */
uint32_t sigma0(uint32_t x) {
    return rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3);
}

/**
 * Sigma1 function used in SHA-256.
 * This is used in the message schedule computation (expanding the message
 * block into sixty-four 32-bit words).
 *
 * @param x The input integer.
 * @return The result of the Sigma1 operation.
 */
uint32_t sigma1(uint32_t x) {
    return rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10);
}

/**
 * The first kind of round constant function Sigma0 used in SHA-256.
 * This is used for generating each round's constant.
 *
 * @param x The input integer.
 * @return The result of the Sigma0 operation.
 */
uint32_t SIGMA0(uint32_t x) {
    return rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22);
}

/**
 * The second kind of round constant function Sigma1 used in SHA-256.
 * This is used for generating each round's constant.
 *
 * @param x The input integer.
 * @return The result of the Sigma1 operation.
 */
uint32_t SIGMA1(uint32_t x) {
    return rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25);
}

/**
 * Byte-swap a 32-bit unsigned integer.
 * This is used for converting between big-endian and little-endian,
 * as SHA-256 uses big-endian conventions.
 *
 * @param val The integer to swap.
 * @return The byte-swapped integer.
 */
uint32_t swap_uint32(uint32_t val) {
    return ((val << 24) & 0xff000000) |
           ((val <<  8) & 0x00ff0000) |
           ((val >>  8) & 0x0000ff00) |
           ((val >> 24) & 0x000000ff);
}
