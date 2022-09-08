#include "Solution.h"
#include <fstream>

bool Solution::is_better_than(const Solution& s) const
{
	return get_score() > s.get_score();
}

Score Solution::get_score() const
{
	//calculate score
	return Score();
}

bool Solution::read()
{
	ifstream in(filename);
	if (!in.is_open())
		return false;
	if (in >> *this)
		return true;
	else
		return false;
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
	//TODO
}

void Solution::undo_swap(Swap swp)
{
	//TODO
}

Swap Solution::get_rand_swap(Random& rnd)
{
	//TODO
	return Swap();
}

ostream& operator<<(ostream& os, const Solution& a)
{
	// TODO: insert return statement here
	return os;
}

istream& operator>>(istream& is, Solution& a)
{
	// TODO: insert return statement here
	//is.clear(ios::goodbit); - koristiti u slucaju da podaci nisu u dobrom formatu
	return is;
}
