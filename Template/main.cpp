//#include <bits/stdc++.h>
#include <vector>
#include <thread>
#include <Windows.h>
#include "Data.h"
#include "Solver.h"
#include "BasicSolver.h"
#include "Solution.h"
#include "Parameters.h"
#include "Optimiser.h"
#include "BasicOptimiser.h"
#include "StartingOptimiser.h"
using namespace std;

const bool continue_from_last_solution = true;

//broj testova
const int num_of_tests = 6;

//da li se pokrece za sve
const bool run_all = true;

//ako se ne pokrece za sve za koji se pokrece
const int which_to_start = 2;

//vreme u sekundama po svakom primeru
const int time_for_each_case = 10;

//Globalne promenljive
mutex output_mutex;

const int starting_optimisers_working_time = 5;
const long long random_bound = (long long) 1e18;

//Ovom promenljivom prekinuti sve cikluse sto pre
bool is_interupted = false;

const int max_num_of_optimisers = 100;

time_t start_time_of_test_case;

void set_i_begin_end(int& i_begin, int& i_end) // konacno
{
    if (run_all)
    {
        i_begin = 0;
        i_end = num_of_tests;
    }
    else
    {
        i_begin = which_to_start;
        i_end = which_to_start + 1;
    }
}

const int num_of_solvers = 1;
Solver** create_solvers() //menjati
{
    Solver** solvers;
    solvers = new Solver * [num_of_solvers];
    solvers[0] = new BasicSolver();
    //Dodati ako postoje jos solvera

    return solvers;
}

Solution solve(const Data& d, int i) //konacno
{
    Solution solution(i);

    if (continue_from_last_solution)
        if (solution.read())
            return solution;

    Solver** solvers;
    solvers = create_solvers();

    for (int j = 0; j < num_of_solvers; ++j)
    {
        Solution tmp_solution(i);
        tmp_solution = solvers[j]->solve(d);
        if (tmp_solution.is_better_than(solution))
            swap(solution, tmp_solution);
    }

    for (int j = 0; j < num_of_solvers; ++j)
        delete solvers[j];
    delete[] solvers;

    return solution;
}

const int num_of_starting_optimisers = 2;
StartingOptimiser** create_starting_optimisers(Solution& solution)
{
    StartingOptimiser** optimisers;
    optimisers = new StartingOptimiser * [num_of_starting_optimisers];
    optimisers[0] = new StartingOptimiser(solution);
    optimisers[1] = new StartingOptimiser(solution);

    return optimisers;
}

Solution wait_for_starting_optimisers(StartingOptimiser** optimisers)
{
    for (int i = 0; i < num_of_starting_optimisers; i++)
        optimisers[i]->join();
    Score best = 0;
    int bestIndex = -1;
    for (int i = 0; i < num_of_starting_optimisers; i++)
    {
        if (bestIndex == -1 || optimisers[i]->getScore() > best)
            bestIndex = i;
    }

    return optimisers[bestIndex]->getSolution();
}

const int num_of_optimisers = 2;
Optimiser** create_optimisers(Solution& solution)
{
    Optimiser** optimisers;
    optimisers = new Optimiser * [num_of_optimisers];
    optimisers[0] = new BasicOptimiser(solution);
    optimisers[1] = new BasicOptimiser(solution);
    //Dodati ako postoje jos optimisera

    return optimisers;
}

void optimise(Solution& solution, int i)
{
    StartingOptimiser** sOptimisers = create_starting_optimisers(solution);

    solution = wait_for_starting_optimisers(sOptimisers);

    Optimiser** optimisers;

    optimisers = create_optimisers(solution);

    for (int k = (int)(time(0) - start_time_of_test_case); k < time_for_each_case; ++k)
    {
        if (GetKeyState('S') & 0x8000)
        {
            solution.lock();
            solution.write();
            solution.unlock();
            cout << "Saved" << endl;
        }
        if (GetKeyState('X') & 0x8000)
        {
            break;
        }
        this_thread::sleep_for(1000ms);
    }

    is_interupted = true;
    for (int j = 0; j < num_of_optimisers; ++j)
        optimisers[j]->join();

    for (int j = 0; j < num_of_optimisers; ++j)
        delete optimisers[j];
}

void solve_all() //konacno
{
    long long score = 0;
    Score opt = 0;
    time_t pt = time(0);

    int i_begin, i_end;
    set_i_begin_end(i_begin, i_end);

    for (int i = i_begin; i < i_end; i++)
    {
        start_time_of_test_case = time(0);
        Data d(i);
        d.read();

        Solution solution(solve(d, i));
        solution.create_mutex();

        Score score_bf_opt = solution.get_score();
        cout << i << ". score before optimisation: " << score_bf_opt << endl;

        optimise(solution, i);
        
        solution.write();

        Score fin_scr = solution.get_score();
        cout << i << "Optimizovano: " << fin_scr - score_bf_opt << endl;
        opt += fin_scr - score_bf_opt;
        cout << i << ". score: " << fin_scr << endl;
        score += fin_scr;

        cout << endl << endl;
    }
    cout << score << endl;
    cout << "Optimizovano: " << opt << endl;
    cout << "Vreme: " << time(0) - pt << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    srand((unsigned) time(0));
    
    solve_all();

    return 0;
}
