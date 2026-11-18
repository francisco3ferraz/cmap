#include "wyhash.h"

void wy_mum(uint64_t *A, uint64_t *B)
{
#if defined(__SIZEOF_INT128__) && !defined(WY_PORTABLE)
    __uint128_t result = (__uint128_t)(*A) * (*B);

    *B = (uint64_t)(result >> 64);
    *A = (uint64_t)result;
#else
    uint32_t a_hi = (uint32_t)(*A >> 32);
    uint32_t a_lo = (uint32_t)(*A);
    uint32_t b_hi = (uint32_t)(*B >> 32);
    uint32_t b_lo = (uint32_t)(*B);

    uint64_t hh = (uint64_t)a_hi * b_hi;
    uint64_t lh = (uint64_t)a_lo * b_hi;
    uint64_t hl = (uint64_t)a_hi * b_lo;
    uint64_t ll = (uint64_t)a_lo * b_lo;

    // handle possible carry bit on lo (1)
    uint64_t part = lh << 32;
    lo += part;
    if (lo < part) hi += 1;

    // handle possible carry bit on lo (2)
    part = hl << 32;
    lo += part;
    if (lo < part) hi += 1;

    *A = lo;
    *B = hi;
#endif
}

uint64_t wy_mix(uint64_t A, uint64_t B) {
    wy_mum(&A, &B);
    return A ^ B;
}