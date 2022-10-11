#pragma once
#include "Solution.h"
#include "Data.h"

class Solver
{
public:
	virtual Solution solve(int case_id, const Data&) = 0;
};

