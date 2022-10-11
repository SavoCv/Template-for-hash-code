#pragma once
#include "Solver.h"

class BasicSolver : public Solver
{
public:
	Solution solve(int case_id, const Data& input_data);
};

