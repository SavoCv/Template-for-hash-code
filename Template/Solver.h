#pragma once
#include "Solution.h"
#include "Data.h"

class Solver
{
public:
	virtual Solution solve(const Data& input_data) = 0;
};

