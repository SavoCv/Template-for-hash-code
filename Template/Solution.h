#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include "Random.h"
#include "Data.h"
using namespace std;

typedef long long Score;
typedef pair<int, int> Swap;

class Solution
{
	Score score;
	bool is_valid_score = false;
	int case_id;
	mutex* mtx;
	string filename;
	const Data* data;
	bool main_solution = false;
	Score last_displayed_score = 0, best;
	time_t last_displayed_score_time = time(0);

	//int timeBeat[500000];
	mutable vector <int> timeBeat;
	vector<int> dems;

	void calcTB();
public:

	Solution(int case_id, const Data& d) : case_id(case_id), score(0), mtx(nullptr), data(&d) {
		filename = string("output") + to_string(case_id) + string(".txt");
		timeBeat.resize(d.D);
	}

	bool is_better_than(Solution&);

	Score get_score();

	bool read();

	void write() const;

	void create_mutex(); // zbog toga sto mutex ne moze da se kopira a solution cemo kopirati vise puta, dakle svaki put kad se iskopira treba pozvati create_mutex

	void delete_mutex();

	void lock();

	void unlock();

	void do_swap(Swap swp);

	void undo_swap(Swap swp);

	Swap get_rand_swap(Random& rnd);

	void setMainSolution(bool m) { main_solution = m; }

	friend ostream& operator<<(ostream& os, const Solution& a);
	friend istream& operator>>(istream& is, Solution& a);

	friend class BasicSolver;

	bool operator==(const Solution& s) {
		if (s.dems.size() != dems.size())
			return false;
		for (int i = 0; i < dems.size(); ++i)
			if (dems[i] != s.dems[i]) {
				cout << i << endl;
				return false;
			}
		return true;
	}
};

