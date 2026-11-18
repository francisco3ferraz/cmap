#include <stdio.h>
#include <inttypes.h>

#include "cmap.h"
#include "wyhash.h"

int main(void) {
    printf("cmap version: %d\n", cmap_version());
    
    printf("hi=%016" PRIx64 " lo=%016" PRIx64 "\n", 3, 5);
    printf("hi=%016" PRIx64 " lo=%016" PRIx64 "\n", 0x100000000, 0x100000000);
    printf("hi=%016" PRIx64 " lo=%016" PRIx64 "\n", 0xFFFFFFFFFFFFFFFF, 2);
    printf("hi=%016" PRIx64 " lo=%016" PRIx64 "\n", 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    return 0;
}