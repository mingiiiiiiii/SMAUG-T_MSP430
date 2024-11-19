#ifndef SMAUG_TOOMCOOK_H
#define SMAUG_TOOMCOOK_H

#include <stdint.h>

#include "parameters.h"

void poly_mul_acc(const int16_t a[LWE_N], const int16_t b[LWE_N], int16_t res[LWE_N]);

#endif	// SMAUG_TOOMCOOK_H
