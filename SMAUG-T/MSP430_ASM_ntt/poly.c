#include <string.h>

#include "poly.h"

//asm functions
extern void ntt_mul_asm(int32_t *r, const int32_t *a, const int32_t *b);
extern void ntt_mul_acc_asm(int32_t *r, const int32_t *a, const int32_t *b);
extern void ct_ntt_merging_asm(int32_t *a);
extern void ct_intt_merging_asm(int32_t *a);

/*************************************************
 * Name:        poly_add
 *
 * Description: Add two polynomials; no modular reduction is performed
 *
 * Arguments: - poly *r: pointer to output polynomial
 *            - poly *a: pointer to first input polynomial
 *            - poly *b: pointer to second input polynomial
 **************************************************/
void poly_add(poly *r, const poly *a, const poly *b) {
	unsigned int i;
	for (i = 0; i < LWE_N; i++)
		r->coeffs[i] = a->coeffs[i] + b->coeffs[i];
}

/*************************************************
 * Name:        poly_sub
 *
 * Description: Subtract two polynomials; no modular reduction is performed
 *
 * Arguments: - poly *r: pointer to output polynomial
 *            - poly *a: pointer to first input polynomial
 *            - poly *b: pointer to second input polynomial
 **************************************************/
void poly_sub(poly *r, const poly *a, const poly *b) {
	unsigned int i;
	for (i = 0; i < LWE_N; i++)
		r->coeffs[i] = a->coeffs[i] - b->coeffs[i];
}

/*************************************************
 * Name:        vec_vec_mult_add_1
 *
 * Description: Multiply two vectors of polynomials and add the result to output
 *              polynomial
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - polyvec *a: pointer to input vector of polynomials
 *              - polyvec *b: pointer to input vector of polynomials (NTT domain)
 *              - uint8_t mod: modulus (16-LOG_P) or (16-LOG_Q)
 **************************************************/
void vec_vec_mult_add_1(poly *r, const polyvec *a, const int32_t b[MODULE_RANK][LWE_N],
											const uint8_t mod) {
	unsigned int i, j;
	poly res;

	int32_t al_tmp[LWE_N] = {0x00};
	int32_t res_tmp[LWE_N] = {0x00};

	for (i = 0; i < MODULE_RANK; ++i) {
		for (j = 0; j < LWE_N; ++j) {
			al_tmp[j] = (int32_t)(int16_t)(a->vec[i].coeffs[j] >> mod);
		}

        ct_ntt_merging_asm(al_tmp);

		if (i == 0) {
            ntt_mul_asm(res_tmp, al_tmp, b[i]);
		} else {
            ntt_mul_acc_asm(res_tmp, al_tmp, b[i]);
		}
	}

    ct_intt_merging_asm(res_tmp);
    
	for (j = 0; j < LWE_N; ++j) {
		//! MLWR 특성으로 저장할 때 left shift, 사용할 때 right shift
		//! 따라서 원래 q로 되돌리지 않아도 된다!
		//! res.coeffs[j] = (uint16_t)(res_tmp[j] & ((1 << LOG_Q) - 1));
		res.coeffs[j] = (uint16_t)(res_tmp[j]);
		res.coeffs[j] <<= mod;
	}

	poly_add(r, r, &res);
}

/*************************************************
 * Name:        vec_vec_mult_add_2
 *
 * Description: Multiply two vectors of polynomials and add the result to output
 *              polynomial
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - polyvec *a: pointer to input vector of polynomials
 *              - polyvec *b: pointer to input vector of polynomials
 *              - uint8_t mod: modulus (16-LOG_P) or (16-LOG_Q)
 **************************************************/
void vec_vec_mult_add_2(poly *r, const polyvec *a, const polyvec *b,
											const uint8_t mod) {
	unsigned int i, j;
	poly res;

	int32_t al_tmp[LWE_N] = {0x00};
	int32_t b_tmp[LWE_N] = {0x00};
	int32_t res_tmp[LWE_N] = {0x00};

	for (i = 0; i < MODULE_RANK; ++i) {
		for (j = 0; j < LWE_N; ++j) {
			al_tmp[j] = (int32_t)(int16_t)(a->vec[i].coeffs[j] >> mod);
			b_tmp[j] = (int32_t)(int16_t)(b->vec[i].coeffs[j]);
		}

        ct_ntt_merging_asm(al_tmp);
        ct_ntt_merging_asm(b_tmp);

		if (i == 0) {
            ntt_mul_asm(res_tmp, al_tmp, b_tmp);
		} else {
            ntt_mul_acc_asm(res_tmp, al_tmp, b_tmp);
		}
	}

    ct_intt_merging_asm(res_tmp);
    
	for (j = 0; j < LWE_N; ++j) {
		//! MLWR 특성으로 저장할 때 left shift, 사용할 때 right shift
		//! 따라서 원래 q로 되돌리지 않아도 된다!
		//! res.coeffs[j] = (uint16_t)(res_tmp[j] & ((1 << LOG_Q) - 1));
		res.coeffs[j] = (uint16_t)(res_tmp[j]);
		res.coeffs[j] <<= mod;
	}

	poly_add(r, r, &res);
}

/*************************************************
 * Name:        matrix_vec_mult_add
 *
 * Description: Transpose the matrix of polynomial and multiply it with the
 *              vector of polynomials.
 *
 * Arguments:   - polyvec *r: pointer to output vector of polynomials
 *              - polyvec *a: pointer to input matrix of polynomials
 *              - polyvec *b: pointer to input vector of polynomials
 **************************************************/
void matrix_vec_mult_add(polyvec *r, const polyvec a[MODULE_RANK],
												 const int32_t b[][LWE_N]) {
	unsigned int i, j, k;

	int32_t at_tmp[LWE_N] = {0x00};
	int32_t res_tmp[LWE_N] = {0x00};

	for (i = 0; i < MODULE_RANK; ++i) {
		for (j = 0; j < MODULE_RANK; ++j) {
			for (k = 0; k < LWE_N; ++k) {
				at_tmp[k] = (int32_t)(int16_t)(a[j].vec[i].coeffs[k] >> _16_LOG_Q);
			}

            ct_ntt_merging_asm(at_tmp);

			if (j == 0) {
                ntt_mul_asm(res_tmp, at_tmp, b[j]);
			} else {
                ntt_mul_acc_asm(res_tmp, at_tmp, b[j]);
			}
		}

        ct_intt_merging_asm(res_tmp);
        
		for (j = 0; j < LWE_N; ++j) {
			// r->vec[i].coeffs[j] = (uint16_t)(res_tmp[j] & ((1 << LOG_Q) - 1));
			r->vec[i].coeffs[j] = (uint16_t)res_tmp[j];
			r->vec[i].coeffs[j] <<= _16_LOG_Q;
		}
	}
}

/*************************************************
 * Name:        matrix_vec_mult_sub
 *
 * Description: Multiply the matrix of polynomial with the vector of polynomial
 *              and subtract the result to output vector of polynomials.
 *
 * Arguments:   - polyvec *r: pointer to in/output vector of polynomials
 *              - polyvec *a: pointer to input matrix of polynomials
 *              - polyvec *b: pointer to input vector of polynomials
 **************************************************/
void matrix_vec_mult_sub(polyvec *r, const polyvec a[MODULE_RANK],
												 const polyvec *b) {
	unsigned int i, j, k;
	poly res;

	int32_t al_tmp[LWE_N] = {0x00};
	int32_t b_tmp[MODULE_RANK][LWE_N] = {0x00};
	int32_t res_tmp[LWE_N] = {0x00};

	for (i = 0; i < MODULE_RANK; i++) {
		for (j = 0; j < LWE_N; j++) {
			b_tmp[i][j] = b->vec[i].coeffs[j];
		}
        ct_ntt_merging_asm(b_tmp[i]);
	}

	for (i = 0; i < MODULE_RANK; ++i) {
		for (j = 0; j < MODULE_RANK; ++j) {
			for (k = 0; k < LWE_N; ++k) {
				al_tmp[k] = (int32_t)(int16_t)(a[i].vec[j].coeffs[k] >> _16_LOG_Q);
			}
            
            ct_ntt_merging_asm(al_tmp);   
			
            if (j == 0) {
                ntt_mul_asm(res_tmp, al_tmp, b_tmp[j]);
			} else {
                ntt_mul_acc_asm(res_tmp, al_tmp, b_tmp[j]);
			}
		}
        
        ct_intt_merging_asm(res_tmp);
		
        for (j = 0; j < LWE_N; ++j) {
			// res.coeffs[j] = (uint16_t)(res_tmp[j] & ((1 << LOG_Q) - 1));
			res.coeffs[j] = (uint16_t)res_tmp[j];
			res.coeffs[j] <<= _16_LOG_Q;
		}

		poly_sub(&r->vec[i], &r->vec[i], &res);
	}
}
