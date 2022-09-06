#pragma once
#include "Solution.h"
#include "Optimiser.h"
#include <thread>

class StartingOptimiser : public Optimiser
{
	Solution copy;

	void optimise();

	thread thr;

	double temperatureFunction(double percentage);

	double P(double oldScore, double newScore, double temp);

public:
	StartingOptimiser(Solution& s);

	void join();
};