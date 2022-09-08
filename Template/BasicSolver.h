#pragma once
#include "Solver.h"

class BasicSolver : public Solver
{
public:
	Solution solve(const Data& input_data);
};

