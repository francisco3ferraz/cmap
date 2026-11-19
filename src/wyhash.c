#include "string.h"

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
    if (lo < part)
        hi += 1;

    // handle possible carry bit on lo (2)
    part = hl << 32;
    lo += part;
    if (lo < part)
        hi += 1;

    *A = lo;
    *B = hi;
#endif
}

uint64_t wy_mix(uint64_t A, uint64_t B)
{
    wy_mum(&A, &B);
    return A ^ B;
}

uint64_t wy_r8(const uint8_t *p)
{
    uint64_t v;
    memcpy(&v, p, sizeof(v));

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = __builtin_bswap64(v);
#endif

    return v;
}

uint64_t wy_r4(const uint8_t *p)
{
    uint32_t v;
    memcpy(&v, p, sizeof(v));

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = __builtin_bswap32(v);
#endif

    return v;
}

uint64_t wy_r3(const uint8_t *p, size_t k)
{
    return ((uint64_t)p[0] << 16) | ((uint64_t)p[k/2] << 8) | (uint64_t)p[k-1];
}