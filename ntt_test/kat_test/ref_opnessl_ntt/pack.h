#ifndef SMAUG_PACK_H
#define SMAUG_PACK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "poly.h"
#include "verify.h"

#define DATA_OFFSET 16

void Rq_to_bytes(uint8_t bytes[PKPOLY_BYTES], const poly *data);
void bytes_to_Rq(poly *data, const uint8_t bytes[PKPOLY_BYTES]);
void Rq_vec_to_bytes(uint8_t bytes[PKPOLYVEC_BYTES], const polyvec *data);
void bytes_to_Rq_vec(polyvec *data, const uint8_t bytes[PKPOLYVEC_BYTES]);
void Rq_mat_to_bytes(uint8_t bytes[PKPOLYMAT_BYTES], const polyvec data[MODULE_RANK]);
void bytes_to_Rq_mat(polyvec data[MODULE_RANK], const uint8_t bytes[PKPOLYMAT_BYTES]);

void Rp_to_bytes(uint8_t bytes[CTPOLY1_BYTES], const poly *data);
void bytes_to_Rp(poly *data, const uint8_t bytes[CTPOLY1_BYTES]);
void Rp2_to_bytes(uint8_t bytes[CTPOLY2_BYTES], const poly *data);
void bytes_to_Rp2(poly *data, const uint8_t bytes[CTPOLY2_BYTES]);
void Rp_vec_to_bytes(uint8_t bytes[CTPOLYVEC_BYTES], const polyvec *data);
void bytes_to_Rp_vec(polyvec *data, const uint8_t bytes[CTPOLYVEC_BYTES]);

void Sx_to_bytes(uint8_t *bytes, const poly *data);
void bytes_to_Sx(poly *data, const uint8_t *bytes);

#endif	// SMAUG_PACK_H
