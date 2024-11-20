
#include "io430.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "kem.h"
#include "parameters.h"

int main() {
	int res;

	uint8_t pk[PUBLICKEY_BYTES] = {0};
	uint8_t sk[KEM_SECRETKEY_BYTES] = {0};
	uint8_t ctxt[CIPHERTEXT_BYTES] = {0};
	uint8_t ss[CRYPTO_BYTES] = {0};
	uint8_t ss2[CRYPTO_BYTES] = {0};

	crypto_kem_keypair(pk, sk);

	res = crypto_kem_enc(ctxt, ss, pk);

	res = crypto_kem_dec(ss2, ctxt, sk);

	if (res != 0) return 1;

	if (memcmp(ss, ss2, CRYPTO_BYTES) != 0) {
		return 1;
	}

	// SMAUG1 : F27D783BC9EC3C152AD7971C3C18E797BBD3570F605676FCC516A6884BB5E709
	// SMAUG3 : 0CA811FE04F107CF697968C2BA9BF57BD866DE32F8301EB3B16467E00728AC96
	// SMAUG5 :	2E6D44894FF7E8622C68DE7AFE2E0098AA1A5700FBE093377FEE123546BC0D5C

	for (int i = 0; i < CRYPTO_BYTES; ++i) {
		printf("%02X", ss[i]);
	}
	printf("\n");

	for (int i = 0; i < CRYPTO_BYTES; ++i) {
		printf("%02X", ss2[i]);
	}
	printf("\n");

	return res;
}
