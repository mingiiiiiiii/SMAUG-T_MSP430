#ifndef PQCLEAN_DILITHIUM3_CLEAN_NTT_H
#define PQCLEAN_DILITHIUM3_CLEAN_NTT_H
#include <stdint.h>

#include "parameters.h"

#define NTT_Q (2424833)
#define NTT_QINV (-2424831)

void ntt(int32_t a[LWE_N]);
void inv_ntt(int32_t a[LWE_N]);
int32_t montgomery_reduce(int64_t a);

#endif