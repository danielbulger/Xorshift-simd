#ifndef XORSHIFT_SIMD_XORWOW_H
#define XORSHIFT_SIMD_XORWOW_H

#include <immintrin.h>

struct xorwow_state
{
	__m128i state[5];

	__m128i counter;

} __attribute__((aligned(16)));

void xorwow_init(struct xorwow_state* state, const int seed[8]);

__m128i xorwow(struct xorwow_state* state);

#endif
