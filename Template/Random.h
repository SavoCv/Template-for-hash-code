#pragma once
#include <random>

using namespace std;

class Random
{
private:
	mt19937 rng;
	std::uniform_int_distribution<mt19937::result_type> udist;
public:
	Random();
	int randomInt(int a, int b);
	long long get_seed();
	int nextInt();
	double nextDouble();
	long long nextLL();
};

