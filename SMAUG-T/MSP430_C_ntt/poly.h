#ifndef SMAUG_POLY_H
#define SMAUG_POLY_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "ntt.h"
#include "parameters.h"

typedef struct {
	int16_t coeffs[LWE_N];
} poly;

typedef struct {
	poly vec[MODULE_RANK];
} polyvec;

void poly_add(poly *r, const poly *a, const poly *b);
void poly_sub(poly *r, const poly *a, const poly *b);

void vec_vec_mult_add_1(poly *r, const polyvec *a, const int32_t b[MODULE_RANK][LWE_N], const uint8_t mod);
void vec_vec_mult_add_2(poly *r, const polyvec *a, const polyvec *b, const uint8_t mod);
void matrix_vec_mult_add(polyvec *r, const polyvec a[MODULE_RANK], const int32_t b[MODULE_RANK][LWE_N]);
void matrix_vec_mult_sub(polyvec *r, const polyvec a[MODULE_RANK], const polyvec *b);

#endif	// SMAUG_POLY_H
