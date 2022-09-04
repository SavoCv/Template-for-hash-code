#pragma once
#include <mutex>
//Parametri i globalne promenljive, definisu se na pocetku main

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

