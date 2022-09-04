#pragma once
#include <iostream>
#include "Random.h"
using namespace std;

typedef long long Score;
typedef pair<int, int> Swap;

class Solution
{
	Score score;
	bool is_valid_score = false;
	int case_id;

public:

	Solution(int case_id) : case_id(case_id), score(0) {}

	bool is_better_than(const Solution&) const;

	Score get_score() const;

	void write() const;

	void lock_for_write(); // u optimiseru kada naidjemo resenje prvo lokujemo zatim proverimo da li je i dalje najbolje resenje i ako jeste onda izvrsimo swap pa onda unlokujemo

	void unlock_for_write();

	void lock_for_read();

	void unlock_for_read();

	void do_swap(Swap swp);

	static const bool undo_exists = false;
	void undo_swap(Swap swp);

	Swap get_rand_swap(Random& rnd);

	friend ostream& operator<<(ostream& os, const Solution& a);
	friend istream& operator>>(istream& is, Solution& a);
};

