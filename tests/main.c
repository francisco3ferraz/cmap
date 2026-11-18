#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#include "cmap.h"
#include "wyhash.h"

static void test_mum(uint64_t a, uint64_t b, uint64_t expected_hi, uint64_t expected_lo)
{
    uint64_t A = a;
    uint64_t B = b;

    wy_mum(&A, &B); // afterwards: A = low half, B = high half

    printf("%016" PRIx64 " * %016" PRIx64 "\n", a, b);
    printf("  got      hi=%016" PRIx64 " lo=%016" PRIx64 "\n", B, A);
    printf("  expected hi=%016" PRIx64 " lo=%016" PRIx64 "\n", expected_hi, expected_lo);

    assert(B == expected_hi);
    assert(A == expected_lo);
}

static void test_mix(uint64_t a, uint64_t b, uint64_t expected)
{
    uint64_t got = wy_mix(a, b);
    printf("mix(%016" PRIx64 ", %016" PRIx64 ") = %016" PRIx64 "\n", a, b, got);
    assert(got == expected);
}

int main(void)
{
    printf("wymap version: %d\n\n", wymap_version());

    test_mum(3, 5, 0, 0xf);
    test_mum(0x100000000, 0x100000000, 1, 0);
    test_mum(0xFFFFFFFFFFFFFFFF, 2, 1, 0xFFFFFFFFFFFFFFFE);
    test_mum(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE, 1);

    test_mix(3, 5, 0xf);
    test_mix(0x100000000, 0x100000000, 1);
    test_mix(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

    printf("\nall mum tests passed\n");
    return 0;
}