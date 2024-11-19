#include "randombytes.h"

int randombytes(uint8_t *x, size_t xlen) {
	for (uint16_t cnt_i = 0; cnt_i < xlen; cnt_i++) x[cnt_i] = cnt_i;

	return xlen;
}
