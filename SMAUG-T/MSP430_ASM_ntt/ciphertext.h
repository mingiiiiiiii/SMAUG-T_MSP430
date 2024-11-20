#ifndef SMAUG_CIPHERTEXT_H
#define SMAUG_CIPHERTEXT_H

#include <stdint.h>

#include "parameters.h"
#include "poly.h"

typedef struct Ciphertext {
    polyvec c1;
    poly c2;
} ciphertext;

void computeC1(polyvec *c1, const polyvec A[MODULE_RANK], const polyvec *r);
void computeC2(poly *c2, const uint8_t delta[DELTA_BYTES], const polyvec *b,
               const polyvec *r);

#endif // SMAUG_CIPHERTEXT_H
