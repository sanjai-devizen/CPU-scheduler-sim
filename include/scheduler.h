#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void simulate_fcfs(process_t* process, int num_process);
void simulate_sjf(process_t* process, int num_process);
void simulate_stcf(process_t* processes, int num_process);
void simulate_rr(process_t* processes, int num_process);
void simulate_mlfq(process_t* processes, int num_process);
void simulate_lottery(process_t* processes, int num_process);
void simulate_stride(process_t* processes, int num_process);

#endif
