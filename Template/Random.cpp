//#include <iostream>
#include <thread>
#include "Random.h"
#include "Parameters.h"

Random::Random() : udist(0,random_bound)
{
	//TODO
	// get seed from somewhere
	mt19937::result_type const seedval = get_seed();
	rng.seed(seedval);
}

int Random::randomInt(int a, int b)
{
	return (int) randomLL(a, b);
}

long long Random::get_seed()
{
	hash <thread::id> hasher;
	return rand() * (long long) hasher(this_thread::get_id());
}

double Random::randomDouble(double a, double b)
{
	return a + nextDouble() * (b - a);
}

double Random::nextDouble()
{
	mt19937::result_type random_number = udist(rng);

	return (double)random_number / (double)random_bound;
}

ll Random::randomLL(ll a, ll b)
{
	mt19937::result_type random_number = udist(rng);

	return random_number % (b - a + 1) + a;
}