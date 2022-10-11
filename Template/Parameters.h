#pragma once
//Parametri i globalne promenljive, definisu se na pocetku main

#include <mutex>
#include <vector>
#include <utility>
using namespace std;

//#define endl "\n"
#define pb push_back
#define mp make_pair
#define MOD 1000000007
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

//broj testova
extern const int num_of_tests;

//da li se pokrece za sve
extern const bool run_all;

//ako se ne pokrece za sve za koji se pokrece
extern const int which_to_start;

//vreme u sekundama po svakom primeru
extern const int time_for_each_case;

//Globalne promenljive
extern mutex output_mutex;

//Ovom promenljivom prekinuti sve cikluse sto pre
extern bool is_interupted;

extern const int max_num_of_optimisers;

//simulated annealing duration in seconds
extern const int starting_optimisers_working_time;

//random range bound
extern const long long random_bound;

extern const int period_of_displaying_score;