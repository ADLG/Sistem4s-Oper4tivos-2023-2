#include "threads/thread.h"
#include "threads/mlfqs-calculations.h"

fixpoint_t
mlfq_calculate_load_avg (fixpoint_t load_avg, int active_threads) 
{
    return fixpoint_div(fixpoint_mult(load_avg,59),60) + fixpoint_div(fixpoint_mult(int_to_fixpoint(active_threads),1),60);
}

fixpoint_t
mlfq_calculate_recent_cpu (fixpoint_t recent_cpu, int nice, fixpoint_t load_avg) 
{
    return fixpoint_mult(fixpoint_div(fixpoint_mult(2,load_avg),(fixpoint_mult(2,load_avg))+1), recent_cpu) + int_to_fixpoint(nice);
}

int 
mlfq_calculate_priority (fixpoint_t recent_cpu, int nice) 
{
    return PRI_MAX - fixpoint_round(fixpoint_div(recent_cpu,4)) - (nice * 2);
}