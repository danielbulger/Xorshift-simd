#include "xorwow.h"

void xorwow_init(struct xorwow_state* state,const int seed[8])
{
	state->state[0] = _mm_set_epi32(seed[3], seed[2], seed[1], seed[0]);
	state->state[1] = _mm_set_epi32(seed[7], seed[6], seed[5], seed[4]);
	state->state[2] = _mm_setzero_si128();
	state->state[3] = _mm_setzero_si128();
	state->state[4] = _mm_setzero_si128();

	// state->counter = (seed1 << 10) ^ (seed2 >> 4)
	state->counter = _mm_xor_si128(
		_mm_slli_epi32(state->state[0], 10),
		_mm_srli_epi32(state->state[1], 4)
	);
}

__m128i xorwow(struct xorwow_state *state)
{
	__m128i t = state->state[4];
	__m128i s = state->state[0];

	state->state[4] = state->state[3];
	state->state[3] = state->state[2];
	state->state[2] = state->state[1];
	state->state[1] = s;

	// t >>= 2
	t = _mm_srli_epi32(t, 2);

	// t ^= t
	t =  _mm_xor_si128(t, t);

	// t <<= 1
	t = _mm_slli_epi32(t, 1);

	// t ^= t
	t =  _mm_xor_si128(t, t);

	// t ^= s ^ (s << 4)
	t =  _mm_xor_si128(t,  _mm_xor_si128(s, _mm_slli_epi32(s, 4)));

	state->state[0] = t;

	// state->counter += 362437
	state->counter = _mm_add_epi32(state->counter, _mm_set1_epi32(362437));

	// return t + state->counter
	return _mm_add_epi32(t, state->counter);
}
