#include <stdint.h>
#include <stdio.h>

// gcc a.c -lm

int is_prime(uint32_t num) {
	if (num == 2 || num == 3) return 1;
	if (num == 1 || num % 2 == 0) return 0;
	for (int i = 3; i * i <= num; i += 2) {
		if (num % i == 0) return 0;
	}
	return 1;
}

int check_low(uint32_t num) {
	if ((num & 0xFFFF) == 1) return 1;
	return 0;
}

int main() {
	//* range = 2 * q/2 * mu * n * k
	int32_t range = 2097152;

	for (; range < 2097152 + 4000000; range++) {
		if (is_prime(range) && check_low(range)) {
			printf("find prime = %d\n", range);
			printf("%d in hex = 0x%08X\n\n", range, range);
			break;
		}
	}
	return 0;
}