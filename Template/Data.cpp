#include <string>
#include "Data.h"

Data::Data(int testcase)
{
	filename = "input" + to_string(testcase) + ".txt";
}

void Data::read()
{
	ifstream inFile;
	inFile.open(filename);

	inFile >> s >> Sm >> T >> D;
	for (int i = 0; i < D; i++) {
		Demon d;
		inFile >> d.sc >> d.tr >> d.sr >> d.na;
		for (int i = 0; i < d.na; i++) {
			int x; inFile >> x;
			d.a.push_back(x);
		}
		d.pref.resize(d.a.size());
		for (int i = 0; i < d.na; i++)
		{
			d.pref[i] = d.a[i];
			if (i > 0) d.pref[i] += d.pref[i - 1];
		}
		demons.push_back(d);
	}

	inFile.close();
}

double Data::koef(const Demon& d) const
{
	/*if (d.na == 0) return -1000;

	int d_sum = d.pref[d.na - 1];

	return d_sum / d.sc;*/

	return 1 / d.tr;
}