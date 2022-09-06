#include "StartingOptimiser.h"

void StartingOptimiser::optimise()
{
	int startTime = time(0);
	const int endTime = 5 * 60;
	int elapsed = 0;
	Random rnd;
	double bestScore = copy.get_score();
	Solution bestSolution = copy;
	while (elapsed <= endTime)
	{
		double temperature = temperatureFunction(elapsed / endTime);
		double oldScore = copy.get_score();
		Swap swp;
		swp = copy.get_rand_swap(rnd);
		copy.do_swap(swp);
		double newScore = copy.get_score();
		if (oldScore < bestScore)
		{
			bestScore = oldScore;
			bestSolution = copy;
		}

		if (P(oldScore, newScore, temperature) < rnd.nextDouble())
		{
			copy.undo_swap(swp);
		}
		elapsed = time(0) - startTime;
	}
}

double StartingOptimiser::temperatureFunction(double percentage)
{
	static double t = 1e9;
	const static double a = 0.999;
	return t = t / (1 + a * t);
}

double StartingOptimiser::P(double oldScore, double newScore, double temp)
{
	if (newScore < oldScore)
		return 1;
	
	return exp((oldScore - newScore)/temp);
}

StartingOptimiser::StartingOptimiser(Solution& s) : copy(s), thr(&StartingOptimiser::optimise, this)
{
}

void StartingOptimiser::join()
{
	thr.join();
}
