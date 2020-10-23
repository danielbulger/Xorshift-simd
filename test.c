#include "xorwow.h"
#include <stdio.h>

int main(int argc, char* args[])
{
	int seed[8] = {
		123456789, 362436069, 521288629, 88675123,
		123456789, 362436069, 521288629, 88675123
	};

	struct xorwow_state state;

	xorwow_init(&state, seed);

	for(int i = 0; i < 600; ++i)
	{
		__m128i rng = xorwow(&state);

		int *val = (int*) &rng;

		printf("%i\t%i\t%i\t%i\n", val[0], val[1], val[2], val[3]);
	}

	return 0;
}