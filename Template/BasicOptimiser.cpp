#include <thread>
#include "BasicOptimiser.h"
#include "Parameters.h"
#include "Random.h"

void BasicOptimiser::optimise()
{
    int pt = time(0);
    Random rnd;
    Solution *tmp;
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
            if (!Solution::undo_exists)
            {
                tmp = new Solution(original);
            }

            original.lock_for_write();
            Score tmp_o_scr = original.get_score(), tmp_o_scr_after_swap;
            original.do_swap(swp);
            if (original.get_score() < tmp_o_scr) {
                if (Solution::undo_exists)
                    original.undo_swap(swp);
                else
                {
                    original = *tmp;
                    delete tmp;
                }
                copy = original;
            }
            original.unlock_for_write();
        }
        //copy.unlock_for_write();
    }
}

BasicOptimiser::BasicOptimiser(Solution& solution) : original(solution), copy(solution), thr(&BasicOptimiser::optimise, this)
{
}


void BasicOptimiser::join()
{
    thr.join();
}
