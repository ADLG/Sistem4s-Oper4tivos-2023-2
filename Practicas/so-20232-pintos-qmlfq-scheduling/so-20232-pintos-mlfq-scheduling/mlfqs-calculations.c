#include "threads/thread.h"
#include "threads/mlfqs-calculations.h"

fixpoint_t
mlfq_calculate_load_avg (fixpoint_t load_avg, int active_threads) 
{
    /* Not yet implemented */
    return 0;
}

fixpoint_t
mlfq_calculate_recent_cpu (fixpoint_t recent_cpu, int nice, fixpoint_t load_avg) 
{
    /* Not yet implemented */
    return 0;
}

int 
mlfq_calculate_priority (fixpoint_t recent_cpu, int nice) 
{
    /* Not yet implemented */
    return 0;
}
