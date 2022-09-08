#pragma once
#include <iostream>
#include <mutex>
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
		filename = "output" + case_id + string(".txt");
	}

	bool is_better_than(const Solution&) const;

	Score get_score() const;

	bool read();

	void write() const;

	void create_mutex(); // zbog toga sto mutex ne moze da se kopira a solution cemo kopirati vise puta, dakle svaki put kad se iskopira treba pozvati create_mutex

	void delete_mutex();

	void lock(); // u optimiseru kada naidjemo resenje prvo lokujemo zatim proverimo da li je i dalje najbolje resenje i ako jeste onda izvrsimo swap pa onda unlokujemo

	void unlock();

	void do_swap(Swap swp);

	static const bool undo_exists = false;
	void undo_swap(Swap swp);

	Swap get_rand_swap(Random& rnd);

	friend ostream& operator<<(ostream& os, const Solution& a);
	friend istream& operator>>(istream& is, Solution& a);
};

