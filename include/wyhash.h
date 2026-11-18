#ifndef WYHASH_H
#define WYHASH_H

#include <stdint.h>

void wy_mum(uint64_t *A, uint64_t *B);
uint64_t wy_mix(uint64_t A, uint64_t B);

#endif