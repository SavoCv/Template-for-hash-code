#include <fstream>
#include <sstream>
#include <queue>
#include "Solution.h"


bool Solution::is_better_than(Solution& s)
{
	return get_score() > s.get_score();
}

void Solution::calcTB()
{
	for (int i = 0; i < data->D; i++)
		timeBeat[i] = -1;
	vector <int> staminaADD(data->T);
	queue<int> q;
	for (int i = 0; i < dems.size(); i++)
		q.push(dems[i]);
	int stam = data->s;
	for (int i = 0; i < data->T; i++)
	{
		stam = min(stam + staminaADD[i], data->Sm);
		if (q.empty())
			break;
		int dem = q.front();
		if (stam >= data->demons[dem].sc)
		{
			stam -= data->demons[dem].sc;
			q.pop();
			timeBeat[dem] = i;
			if (i + data->demons[dem].tr < data->T)
				staminaADD[i + data->demons[dem].tr] += data->demons[dem].sr;
		}
	}
}

Score Solution::get_score()
{
	calcTB();
	Score sc = 0;
	for (int i = 0; i < data->D; i++)
	{
		if (timeBeat[i] == -1) continue;
		int len = min(data->T - timeBeat[i], (int)data->demons[i].a.size());
		if (len > 0) sc += data->demons[i].pref[len - 1];
	}

	if (main_solution && time(0) - last_displayed_score_time >= period_of_displaying_score)
	{
		stringstream ss;
		
		ss << best << "\t\t";
		if (best > last_displayed_score)
			ss << "+";
		ss << best - last_displayed_score << endl;
		cout << ss.str();

		if (best > last_displayed_score)
			last_displayed_score = best;
		last_displayed_score_time = time(0);
	}

	if (sc > best)
		best = sc;
	return sc;
}

bool Solution::read()
{
	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Can't open last solution" << endl;
		return false;
	}
	try {
		in >> *this;
		return true;
	}
	catch(exception e) {
		cerr << e.what() << endl;
		return false;
	}
}

void Solution::write() const
{
	ofstream out(filename);
	out << *this;
}

void Solution::create_mutex()
{
	mtx = new mutex();
}

void Solution::delete_mutex()
{
	delete mtx;
}

void Solution::lock()
{
	if (mtx == nullptr)
		throw exception("Mora se pozvati funkcija create_mutex za solution pre pozivanja lock");
	mtx->lock();
}

void Solution::unlock()
{
	mtx->unlock();
}

void Solution::do_swap(Swap swp)
{
	swap(dems[swp.first], dems[swp.second]);
}

void Solution::undo_swap(Swap swp)
{
	do_swap(swp);
}

Swap Solution::get_rand_swap(Random& rnd)
{
	return make_pair(rnd.randomInt(0, dems.size() - 1), rnd.randomInt(0, dems.size() - 1));
}

ostream& operator<<(ostream& os, const Solution& a)
{
	// TODO: insert return statement here
	string line;
	for (int i = 0; i < a.dems.size(); i++)
		os << a.dems[i] << endl;
	return os;
}

istream& operator>>(istream& is, Solution& a)
{
	// TODO: insert return statement here
	a.dems.clear();
	int x;
	while (is >> x)
	{
		a.dems.push_back(x);
		//cout << x;
	}
	return is;
}
