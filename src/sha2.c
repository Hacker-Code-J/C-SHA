#include "sha2.h"

// Initialize the SHA-2 message digest with a given seed
void sha2_init(sha2_t *sha2, uint32_t seed) {
    memset(sha2->state, 0, sizeof(sha2->state));
    sha2->count = seed;
}

// Update the SHA-2 message digest with a given block of data
void sha2_update(sha2_t *sha2, const void *data, size_t len) {
    while (len >= 64) {
        uint32_t words[16];
        for (int i = 0; i < 16; i++) {
            words[i] = ((uint32_t *)data)[i];
        }
        sha2->state[0] += words[0];
        sha2->state[1] += words[1];
        sha2->state[2] += words[2];
        sha2->state[3] += words[3];
        sha2->state[4] += words[4];
        sha2->state[5] += words[5];
        sha2->state[6] += words[6];
        sha2->state[7] += words[7];
        for (int i = 0; i < 64; i++) {
            sha2->buffer[i] ^= ((uint8_t *)&words[i])[i & 3];
        }
        len -= 64;
        data += 64;
    }
}

// Finalize the SHA-2 message digest and return the resulting hash
void sha2_final(sha2_t *sha2, uint8_t *hash) {
    sha2->state[0] = (sha2->state[0] & 0xff000000) | ((sha2->state[0] >> 24) & 0x00ffffff);
    sha2->state[1] = (sha2->state[1] & 0x00ffffff) | ((sha2->state[1] << 8) & 0xff000000);
    sha2->state[2] = (sha2->state[2] & 0x00ffffff) | ((sha2->state[2] << 16) & 0xff000000);
    sha2->state[3] = (sha2->state[3] & 0x00ffffff) | ((sha2->state[3] << 24) & 0xff000000);
    sha2->count += 64;
    for (int i = 0; i < 8; i++) {
        hash[i] = (uint8_t)(sha2->state[i] >> 24);
        hash[i + 1] = (uint8_t)(sha2->state[i] >> 16);
        hash[i + 2] = (uint8_t)(sha2->state[i] >> 8);
        hash[i + 3] = (uint8_t)sha2->state[i];
    }
}

// #include "sha2.h"
// #include "sha2_utils.h"

// // SHA-256 Constants: The first 32 bits of the fractional parts of the cube roots of the first 64 primes (2..311)
// static const uint32_t k[64] = {
//     0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
//     0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
//     // ... and so on for all 64 constants
// };

// /**
//  * Initialize the SHA-256 context.
//  *
//  * @param ctx Pointer to the SHA256_CTX structure to initialize.
//  */
// void sha256_init(SHA256_CTX *ctx) {
//     ctx->bitCount = 0;
//     ctx->state[0] = 0x6a09e667;
//     ctx->state[1] = 0xbb67ae85;
//     ctx->state[2] = 0x3c6ef372;
//     ctx->state[3] = 0xa54ff53a;
//     ctx->state[4] = 0x510e527f;
//     ctx->state[5] = 0x9b05688c;
//     ctx->state[6] = 0x1f83d9ab;
//     ctx->state[7] = 0x5be0cd19;
// }

// /**
//  * Process a block of data and update the SHA-256 context.
//  *
//  * @param ctx Pointer to the SHA256_CTX structure.
//  * @param data The data block to process.
//  */
// static void sha256_transform(SHA256_CTX *ctx, const uint8_t data[]) {
//     uint32_t a, b, c, d, e, f, g, h, i, j, temp1, temp2, m[64];

//     for (i = 0, j = 0; i < 16; ++i, j += 4)
//         m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
//     for ( ; i < 64; ++i)
//         m[i] = sigma1(m[i - 2]) + m[i - 7] + sigma0(m[i - 15]) + m[i - 16];

//     a = ctx->state[0];
//     b = ctx->state[1];
//     c = ctx->state[2];
//     d = ctx->state[3];
//     e = ctx->state[4];
//     f = ctx->state[5];
//     g = ctx->state[6];
//     h = ctx->state[7];

//     for (i = 0; i < 64; ++i) {
//         temp1 = h + SIGMA1(e) + ch(e, f, g) + k[i] + m[i];
//         temp2 = SIGMA0(a) + maj(a, b, c);
//         h = g;
//         g = f;
//         f = e;
//         e = d + temp1;
//         d = c;
//         c = b;
//         b = a;
//         a = temp1 + temp2;
//     }

//     ctx->state[0] += a;
//     ctx->state[1] += b;
//     ctx->state[2] += c;
//     ctx->state[3] += d;
//     ctx->state[4] += e;
//     ctx->state[5] += f;
//     ctx->state[6] += g;
//     ctx->state[7] += h;
// }

// /**
//  * Add data to the SHA-256 context, processing it in blocks.
//  *
//  * @param ctx Pointer to the SHA256_CTX structure.
//  * @param data Pointer to the data to hash.
//  * @param len Length of the data in bytes.
//  */
// void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len) {
//     uint32_t i;

//     for (i = 0; i < len; ++i) {
//         ctx->buffer[ctx->bitCount / 8 % 64] = data[i];
//         ctx->bitCount += 8;
//         if (ctx->bitCount % 512 == 0) {
//             sha256_transform(ctx, ctx->buffer);
//         }
//     }
// }

// /**
//  * Finalize the SHA-256 hash and output the result.
//  *
//  * @param ctx Pointer to the SHA256_CTX structure.
//  * @param hash Output buffer for the hash (32 bytes).
//  */
// void sha256_final(SHA256_CTX *ctx, uint8_t hash[]) {
//     uint32_t i = ctx->bitCount / 8 % 64;

//     // Pad the final block
//     ctx->buffer[i++] = 0x80; // Append a single '1' bit
//     if (i > 56) {
//         while (i < 64)
//             ctx->buffer[i++] = 0;
//         sha256_transform(ctx, ctx->buffer);
//         i = 0;
//     }
//     while (i < 56)
//         ctx->buffer[i++] = 0;

//     // Append the length in bits at the end of the buffer
//     ctx->buffer[63] = ctx->bitCount;
//     ctx->buffer[62] = ctx->bitCount >> 8;
//     ctx->buffer[61] = ctx->bitCount >> 16;
//     ctx->buffer[60] = ctx->bitCount >> 24;
//     ctx->buffer[59] = ctx->bitCount >> 32;
//     ctx->buffer[58] = ctx->bitCount >> 40;
//     ctx->buffer[57] = ctx->bitCount >> 48;
//     ctx->buffer[56] = ctx->bitCount >> 56;
//     sha256_transform(ctx, ctx->buffer);

//     // Output the final hash
//     for (i = 0; i < 4; ++i) {
//         hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
//         hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
//     }
// }
