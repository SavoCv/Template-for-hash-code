#include "Random.h"

Random::Random() : udist(0,1e18)
{
	//TODO
	mt19937::result_type const seedval = get_seed(); // get this from somewhere
	rng.seed(seedval);
}

int Random::randomInt(int a, int b)
{
	mt19937::result_type random_number = udist(rng);

	return random_number % (b - a + 1) + a;
}

long long Random::get_seed()
{
	return 1e9 + 7; // TODO
}

int Random::nextInt()
{
	//TODO
	return 0;
}
