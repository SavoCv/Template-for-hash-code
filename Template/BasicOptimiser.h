#pragma once
#include "Optimiser.h"

class BasicOptimiser : public Optimiser
{
public:
	BasicOptimiser(int num_of_threads);

	void start();

	void join();
};

