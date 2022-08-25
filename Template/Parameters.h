#pragma once
#include <mutex>
//Parametri i globalne promenljive

//broj testova
const int num_of_tests = 6;

//da li se pokrece za sve
const bool run_all = true;

//ako se ne pokrece za sve za koji se pokrece
const int which_to_start = 2;

//vreme u sekundama po svakom primeru
const int time_for_each_case = 30;

//Globalne promenljive
mutex output_mutex;

//Ovom promenljivom prekinuti sve cikluse sto pre
bool is_interupted = false;

const int max_num_of_optimisers = 100;