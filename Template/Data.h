#pragma once
#include <fstream>
#include <vector>
using namespace std;
class Data
{
private:
	//TODO
	string filename;

	struct Demon {
		int sc, tr, sr, na;
		vector<int> a;
		vector<int> pref;
	};

	vector<Demon> demons;

	int s, Sm, T, D;

public:
	Data(int);
	void read();

	int getD() const { return D; }

	double koef(const Demon& d) const;

	friend class Solution;
	friend class BasicSolver;
};

