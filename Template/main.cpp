//#include <bits/stdc++.h>
#include <vector>
#include <thread>
#include "Data.h"
#include "Solver.h"
#include "BasicSolver.h"
#include "Solution.h"
#include "Parameters.h"
#include "Optimiser.h"
#include "BasicOptimiser.h"
#include <Windows.h>

using namespace std;

#define endl "\n"
#define pb push_back
#define mp make_pair
#define MOD 1000000007
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

struct Res
{

};

Res best;

bool isValid(const Res& res)
{
    //TO DO
    return true;
}

void doRandomSwap(Res& res)
{
    //TO DO
}

int scoreRes(const Res& res)
{
    //TO DO
    return 0;
}

bool isBetter(const Res& res)
{
    //TO DO
    return false;
}


int optimisation(int vreme = 10)
{
    static Res r;
    r = best;
    int pt = time(0);
    int best_score = scoreRes(best), tmp;
    int p_score = best_score;
    while (time(0) - pt < vreme)
    {
        doRandomSwap(r);
        if (isValid(r) && (tmp = scoreRes(r)) >= best_score) {
            best = r;
            best_score = tmp;
        }
        else {
            r = best;
            // moze i funkcija undoLastSwap(r) koja bi mogla brze da radi
        }
    }
    cout << "Optimizacija: " << (tmp = scoreRes(best) - p_score) << endl;
    cout << "Vreme: " << time(0) - pt << endl;
    return tmp;
}

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

void solve_all() //konacno
{
    long long score = 0;
    Score opt = 0;
    int pt = time(0);

    int i_begin, i_end;
    set_i_begin_end(i_begin, i_end);

    for (int i = i_begin; i < i_end; i++)
    {
        Data d(i);
        d.read();

        Solution solution(solve(d, i));

        Score score_bf_opt = solution.get_score();
        cout << i << ". score before optimisation: " << score_bf_opt << endl;

        const int num_of_optimisers = 1;
        Optimiser* optimisers[1];
        
        optimisers[0] = new BasicOptimiser(4);
        for (int j = 0; j < num_of_optimisers; ++j)
        {
            optimisers[j]->start(); 
        }
        
        for (int k = 0; k < time_for_each_case; ++k)
        {
            if (GetKeyState('s') & 1)
            {
                is_interupted = true;
                for (int j = 0; j < num_of_optimisers; ++j) {
                    optimisers[j]->join();
                }
                solution.write();
                cout << "Saved" << endl;
            }
            this_thread::sleep_for(1000ms);
        }

        is_interupted = true;
        for (int j = 0; j < num_of_optimisers; ++j)
            optimisers[j]->join();
        solution.write();

        Score fin_scr = solution.get_score();
        cout << i << "Optimizovano: " << fin_scr - score_bf_opt << endl;
        opt += fin_scr - score_bf_opt;
        cout << i << ". score: " << fin_scr << endl;
        score += fin_scr;

        for (int j = 0; j < num_of_optimisers; ++j)
            delete optimisers[j];

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
    srand(time(0));
    
    solve_all();


    //thread t(solveAll);
    //solveAll();

    //t.join();

    return 0;
}
