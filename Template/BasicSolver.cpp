#include "BasicSolver.h"
#include "Solution.h"

Solution BasicSolver::solve(int case_id, const Data& input_data)
{
    //TODO
    Solution best(case_id ,input_data);

	best.dems.clear();
	best.dems.resize(input_data.D);
	
	for (int i = 0; i < input_data.D; i++)
		best.dems[i] = i;

	sort(best.dems.begin(), best.dems.end(), [&input_data](int i, int j) {

		const Data::Demon& a = input_data.demons[i];
		const Data::Demon& b = input_data.demons[j];


		return input_data.koef(a) > input_data.koef(b);
		//return input_data.demons[i].sc < input_data.demons[j].sc;
		//return a.pref[a.na-1] < b.pref[b.na-1];
		});

	//best.dems.resize(input_data.D);
	//best.dems = ans;
	random_shuffle(best.dems.begin(), best.dems.end());

	return best;
}
