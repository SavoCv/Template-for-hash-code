#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include "Random.h"
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

public:

	Solution(int case_id) : case_id(case_id), score(0), mtx(nullptr) {
		filename = string("output") + to_string(case_id) + string(".txt");
	}

	bool is_better_than(const Solution&) const;

	Score get_score() const;

	bool read();

	void write() const;

	void create_mutex(); // zbog toga sto mutex ne moze da se kopira a solution cemo kopirati vise puta, dakle svaki put kad se iskopira treba pozvati create_mutex

	void delete_mutex();

	void lock();

	void unlock();

	void do_swap(Swap swp);

	void undo_swap(Swap swp);

	Swap get_rand_swap(Random& rnd);

	friend ostream& operator<<(ostream& os, const Solution& a);
	friend istream& operator>>(istream& is, Solution& a);
};

