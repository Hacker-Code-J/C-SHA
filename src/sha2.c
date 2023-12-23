#include "sha2.h"
#include "sha2_utils.h"

// SHA-256 Constants: The first 32 bits of the fractional parts of the cube roots of the first 64 primes (2..311)
static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    // ... and so on for all 64 constants
};

/**
 * Initialize the SHA-256 context.
 *
 * @param ctx Pointer to the SHA256_CTX structure to initialize.
 */
void sha256_init(SHA256_CTX *ctx) {
    ctx->bitCount = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

/**
 * Process a block of data and update the SHA-256 context.
 *
 * @param ctx Pointer to the SHA256_CTX structure.
 * @param data The data block to process.
 */
static void sha256_transform(SHA256_CTX *ctx, const uint8_t data[]) {
    uint32_t a, b, c, d, e, f, g, h, i, j, temp1, temp2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for ( ; i < 64; ++i)
        m[i] = sigma1(m[i - 2]) + m[i - 7] + sigma0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        temp1 = h + SIGMA1(e) + ch(e, f, g) + k[i] + m[i];
        temp2 = SIGMA0(a) + maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

/**
 * Add data to the SHA-256 context, processing it in blocks.
 *
 * @param ctx Pointer to the SHA256_CTX structure.
 * @param data Pointer to the data to hash.
 * @param len Length of the data in bytes.
 */
void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len) {
    uint32_t i;

    for (i = 0; i < len; ++i) {
        ctx->buffer[ctx->bitCount / 8 % 64] = data[i];
        ctx->bitCount += 8;
        if (ctx->bitCount % 512 == 0) {
            sha256_transform(ctx, ctx->buffer);
        }
    }
}

/**
 * Finalize the SHA-256 hash and output the result.
 *
 * @param ctx Pointer to the SHA256_CTX structure.
 * @param hash Output buffer for the hash (32 bytes).
 */
void sha256_final(SHA256_CTX *ctx, uint8_t hash[]) {
    uint32_t i = ctx->bitCount / 8 % 64;

    // Pad the final block
    ctx->buffer[i++] = 0x80; // Append a single '1' bit
    if (i > 56) {
        while (i < 64)
            ctx->buffer[i++] = 0;
        sha256_transform(ctx, ctx->buffer);
        i = 0;
    }
    while (i < 56)
        ctx->buffer[i++] = 0;

    // Append the length in bits at the end of the buffer
    ctx->buffer[63] = ctx->bitCount;
    ctx->buffer[62] = ctx->bitCount >> 8;
    ctx->buffer[61] = ctx->bitCount >> 16;
    ctx->buffer[60] = ctx->bitCount >> 24;
    ctx->buffer[59] = ctx->bitCount >> 32;
    ctx->buffer[58] = ctx->bitCount >> 40;
    ctx->buffer[57] = ctx->bitCount >> 48;
    ctx->buffer[56] = ctx->bitCount >> 56;
    sha256_transform(ctx, ctx->buffer);

    // Output the final hash
    for (i = 0; i < 4; ++i) {
        hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}
