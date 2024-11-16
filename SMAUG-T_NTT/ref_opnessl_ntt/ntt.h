#ifndef PQCLEAN_DILITHIUM3_CLEAN_NTT_H
#define PQCLEAN_DILITHIUM3_CLEAN_NTT_H
#include <stdint.h>

#include "parameters.h"

void ntt(int32_t a[LWE_N]);

void invntt_tomont(int32_t a[LWE_N]);
int32_t montgomery_reduce(int64_t a);

#endif