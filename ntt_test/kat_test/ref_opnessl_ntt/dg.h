#ifndef SMAUG_DG_H
#define SMAUG_DG_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dg.h"
#include "fips202.h"
#include "parameters.h"
#include "poly.h"
#include "randombytes.h"
#include "verify.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// NOISE DISTRIBUTION ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// error distribution for LWE instances in public key generation:
// store probability table (CDF_TABLE)
// sample a single error from (RANDBITS)-length of random binary string

// A discrete error distribution close to the discrete Gaussian distribution
int addGaussianError(poly *op, const uint8_t *seed);
void addGaussianErrorVec(polyvec *op, const uint8_t seed[CRYPTO_BYTES]);

#endif	// SMAUG_DG_H
