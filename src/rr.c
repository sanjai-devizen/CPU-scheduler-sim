#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/scheduler.h"
#include "../include/queue.h"
#include "../include/display.h"

#define RR_QUANTUM 4 

void simulate_rr(process_t* processes, int num_processes){
    queue_t* ready_queue = queue_init();

    unsigned int current_time = 0;
    int completed_processes = 0;
    process_t* current_process = NULL;
    int current_slice = 0;

    printf("\n----Starting RR Scheduling (Quantum: %d)----\n\n", RR_QUANTUM);
	init_display(num_processes);

    while(completed_processes < num_processes){

        for(int i = 0; i < num_processes; i++){
            if ((processes + i)->arrival_time == current_time){
                queue_enqueue(ready_queue, processes + i);
            }
        }

        if (current_process != NULL && current_slice == RR_QUANTUM && current_process->remaining_time > 0){
            //printf("[Time : %d] Process %d exhausted its quantum, context switch !\n", current_time, current_process->pid);
            queue_enqueue(ready_queue, current_process);
            current_process = NULL;
        }

        if (current_process == NULL && !queue_is_empty(ready_queue)){
            queue_dequeue(ready_queue, &current_process);
            current_slice = 0;

            if (current_process->burst_time == current_process->remaining_time)
                current_process->start_time = current_time;
        }

        if (current_process != NULL){
            //printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);
            
            current_process->remaining_time--;
            current_slice++;

            if (current_process->remaining_time == 0){
                current_process->completion_time = current_time + 1;
                current_process->response_time = current_process->start_time - current_process->arrival_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;

                //printf("[Time : %d] Process %d is completed.\n", current_time + 1, current_process->pid);
                //printf("-----> turnaround time : %d, response time : %d\n\n", current_process->turnaround_time, current_process->response_time);

                completed_processes++;
                current_process = NULL;
            }
        } //else {
            //printf("[Time : %d] CPU is idle.\n", current_time);
        //}

		render_process(current_time, current_process, num_processes);
        current_time++;
        sleep(1);
    }

	display_summary(processes, num_processes);
    free(ready_queue);
    printf("RR simulation completed successfully !\n");
}