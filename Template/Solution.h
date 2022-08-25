#pragma once
#include <iostream>
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

	void lock(); // u optimiseru kada naidjemo resenje prvo lokujemo zatim proverimo da li je i dalje najbolje resenje i ako jeste onda izvrsimo swap pa onda unlokujemo

	void unlock();

	void do_swap(Swap swp);

	friend ostream& operator<<(ostream& os, const Solution& a);
	friend istream& operator>>(istream& is, Solution& a);
};

