#include <stdio.h>
#include "sha2.h"

int main() {
    sha2_t sha2;
    
    // Initialize the SHA-2 message digest with a given seed
    uint32_t seed = 0xdeadbeef;
    sha2_init(&sha2, seed);

    // Update the message digest with some data
    char *data = "hello world";
    size_t len = strlen(data);
    sha2_update(&sha2, data, len);

    // Finalize the message digest and get the resulting hash
    uint8_t hash[32];
    sha2_final(&sha2, hash);

    for(int i = 0; i< 32; i++)
        printf("%02x:", hash[i]);

    return;
}