#pragma once
#include <random>
#include "Parameters.h"

using namespace std;

class Random
{
private:
	mt19937 rng;
	std::uniform_int_distribution<mt19937::result_type> udist;
	long long get_seed();
public:
	Random();
	int randomInt(int a, int b);
	double randomDouble(double a, double b);
	ll randomLL(ll a, ll b);
	double nextDouble();
};

