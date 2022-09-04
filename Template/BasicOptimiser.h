#pragma once
#include "Optimiser.h"
#include "Solution.h"

class BasicOptimiser : public Optimiser
{
	Solution copy;
	Solution& original;

	void optimise();

	thread thr;

public:
	BasicOptimiser(Solution& s);

	void join();
};

