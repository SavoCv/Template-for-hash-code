#include <thread>
#include "BasicOptimiser.h"
#include "Parameters.h"
#include "Random.h"

void BasicOptimiser::optimise()
{
    time_t pt = time(0);
    Random rnd;
    int cnt = 0;
    while (!is_interupted)
    {
        Swap swp;
        //copy.lock_for_write();
        Score tmp_scr = copy.get_score();
        swp = copy.get_rand_swap(rnd);
        copy.do_swap(swp);
        
        if (copy.get_score() >= tmp_scr)
        {
            original.lock();
            Score tmp_o_scr = original.get_score();
            original.do_swap(swp);
            if (original.get_score() < tmp_o_scr) {
                original.undo_swap(swp);
                copy = original;
                copy.setMainSolution(false);
                //cout << "a" << endl;
            }
            original.unlock();
        }
        else
            copy.undo_swap(swp);
        //copy.unlock_for_write();
        cnt++;
    }
}

BasicOptimiser::BasicOptimiser(Solution& solution) : original(solution), copy(solution), thr(&BasicOptimiser::optimise, this)
{
    copy.create_mutex();
}


void BasicOptimiser::join()
{
    thr.join();
}
