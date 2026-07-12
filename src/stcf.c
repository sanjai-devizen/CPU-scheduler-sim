#include <stdio.h>
#include <unistd.h>
#include "../include/scheduler.h"
#include "../include/display.h"

void simulate_stcf(process_t* processes, int num_process){
    unsigned int current_time = 0;
    int completed_processes = 0;
    process_t* current_process = NULL;

    printf("\n--- Starting Preemptive STCF Simulation ---\n");
	init_display(num_process);

    while(completed_processes < num_process){
        int shortest_index = -1;
        unsigned int min_remaining_time = __UINT32_MAX__; 

        for(int i = 0; i < num_process; ++i){
            process_t* p = processes + i;

            if (p->arrival_time <= current_time && p->remaining_time > 0){
                if (p->remaining_time < min_remaining_time){
                    min_remaining_time = p->remaining_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index != -1){
            process_t* next_process = processes + shortest_index;

            if (current_process != next_process) {
                if (current_process != NULL) {
                    //printf("[Time : %d] Context Switch: Process %d preempted by Process %d.\n", current_time, current_process->pid, next_process->pid);
                }
                    
                current_process = next_process;
                    
                if (current_process->remaining_time == current_process->burst_time) {
                    current_process->start_time = current_time;
                }   
            }
        }

        if (current_process != NULL){
            //printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);
            
            current_process->remaining_time--;

            if (current_process->remaining_time == 0){
                current_process->completion_time = current_time + 1;

                current_process->response_time = current_process->start_time - current_process->arrival_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;

                //printf("-----> turnaround time : %d, response time : %d\n\n", current_process->turnaround_time, current_process->response_time);

                completed_processes++;
                current_process = NULL;
            }
        } //else {
            //printf("[Time : %d] CPU is idle\n", current_time);
        //}

		render_process(current_time, current_process, num_process);
        current_time++;
        sleep(1);
    }

	display_summary(processes, num_process);
    printf("STCF simulation complete !\n");
}