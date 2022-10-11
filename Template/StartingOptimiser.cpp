#include <climits>
#include <float.h>
#include "StartingOptimiser.h"
#include "Parameters.h"

//simulated annealing
//Potenital problem : saving the best solution by doing copy too many times
//Potenital solutions
//-maybe just take copy at the end without saving in between
//-store every swap and then just remember the index where the best result was 
//and then just perform these swaps from the beginning
void StartingOptimiser::optimise()
{
	int startTime = time(0);
	int elapsed = 0;
	Random rnd;
	Score bestScore = copy.get_score();
	Solution bestSolution = copy;
	while (elapsed <= starting_optimisers_working_time)
	{
		double temperature = temperatureFunction(elapsed / starting_optimisers_working_time);
		//cout << temperature << " ";
		Score oldScore = copy.get_score();
		Swap swp;
		swp = copy.get_rand_swap(rnd);
		copy.do_swap(swp);
		Score newScore = copy.get_score();
		
		/*if (oldScore < bestScore)
		{
			bestScore = oldScore;
			bestSolution = copy;
		}*/


		//cout << P(oldScore, newScore, temperature) << endl;
		if (P(oldScore, newScore, temperature) < rnd.nextDouble())
		{
			copy.undo_swap(swp);
		}
		elapsed = time(0) - startTime;
	}
	//copy = bestSolution;
}

//TODO testing
double StartingOptimiser::temperatureFunction(double percentage)
{
	static double t = 1e9;
	const static double a = 0.999;
	return t = t / (1 + a * t);
}

//TODO testing
double StartingOptimiser::P(double oldScore, double newScore, double temp)
{
	if (newScore > oldScore)
		return 1;
	if (exp((oldScore - newScore) / temp) >= DBL_MAX)
		return 0;
	//if (temp < 1e-4) return 0;
	return exp((oldScore - newScore)/temp);
}

StartingOptimiser::StartingOptimiser(Solution& s) : copy(s), thr(&StartingOptimiser::optimise, this)
{
}

void StartingOptimiser::join()
{
	thr.join();
}
