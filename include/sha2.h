#ifndef _SHA2_H
#define _SHA2_H

#include <stdint.h>
#include <string.h>

// Define the SHA-2 message digest structure
typedef struct {
    uint32_t state[8];
    uint64_t count;
    uint8_t buffer[64];
} sha2_t;

void sha2_init(sha2_t *sha2, uint32_t seed);
void sha2_update(sha2_t *sha2, const void *data, size_t len);
void sha2_final(sha2_t *sha2, uint8_t *hash);

// #include <stdint.h> // Include standard integer types
// #include <stddef.h> // Include the definition of size_t

// // Define constants for SHA-256
// #define SHA256_BLOCK_SIZE 32 // SHA-256 outputs a 32-byte digest

// // SHA-256 context structure
// // This structure will hold context information for the SHA-256 hashing operation
// typedef struct {
//     uint32_t state[8];       // Current state (A, B, C, D, E, F, G, H)
//     uint64_t bitCount;       // Total number of bits processed
//     uint8_t  buffer[64];     // Data block being processed
// } SHA256_CTX;

// // Function prototypes for SHA-256
// void sha256_init(SHA256_CTX *ctx);
// void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len);
// void sha256_final(SHA256_CTX *ctx, uint8_t hash[]);

#endif // _SHA2_H
