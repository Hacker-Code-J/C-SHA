#ifndef _SHA2_UTILS_H
#define _SHA2_UTILS_H

#include <stdint.h>

// Define utility functions and constants here

// For example, you can define common operations used in the SHA-2 algorithm:
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define SIG1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG2(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

// Other helper functions like byte-swapping can also be declared here
uint32_t swap_uint32(uint32_t val);

#endif // _SHA2_UTILS_H
