#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "../include/scheduler.h"
#include "../include/display.h"

#define STRIDE_NUMERATOR 10000

void simulate_stride(process_t* processes, int num_process){
	unsigned int current_time = 0;
	int completed_processes = 0;
	process_t* current_process = NULL;

	int global_min_pass = 0;
	init_display(num_process);
	
	while(completed_processes < num_process){
		current_process = NULL;
		unsigned int min_pass = UINT_MAX;

		for(int i = 0; i < num_process; i++){
			if ((processes + i)->arrival_time <= current_time && (processes + i)->remaining_time > 0){
				if ((processes + i)->arrival_time == current_time && (processes + i)->remaining_time == (processes + i)->burst_time){
					if ((processes + i)->arrival_time <= current_time && (processes + i)->remaining_time > 0){
						unsigned int safe_tickets = (processes + i)->tickets > 0 ? (processes + i)->tickets : 1;
						(processes + i)->stride = STRIDE_NUMERATOR / safe_tickets;

						(processes + i)->pass = global_min_pass;
					}
				}

				if ((processes + i)->pass < min_pass){
					min_pass = (processes + i)->pass;
					current_process = processes + i;
				}
			}
		}

		if (current_process != NULL){
			global_min_pass = min_pass;

			if (current_process->remaining_time == current_process->burst_time){
				current_process->start_time = current_time;
			}

			//printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);

			current_process->remaining_time--;
			current_process->pass = current_process->pass + current_process->stride;

			if (current_process->remaining_time == 0){
				current_process->completion_time = current_time;

                current_process->response_time = current_process->start_time - current_process->arrival_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;

                //printf("-----> turnaround time : %d, response time : %d\n\n", current_process->turnaround_time, current_process->response_time);

                completed_processes++;
			}
		} //else printf("[Time : %d] CPU is idle.\n", current_time);

		render_process(current_time, current_process, num_process);
		current_time++;
		sleep(1);
	}

	display_summary(processes, num_process);
	printf("\nSTRIDE scheduling simulation successfully completed !\n");
}
