#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/scheduler.h"
#include "../include/display.h"

void simulate_lottery(process_t* processes, int num_processes){
	unsigned int current_time = 0;
	int completed_processes = 0;
	process_t* current_process = NULL;
	printf("\n----Starting lottery scheduling----\n");
	init_display(num_processes);

	while(completed_processes < num_processes){
		int total_tickets = 0;

		for(int i = 0; i < num_processes; i++){
			if ((processes + i)->arrival_time <= current_time && (processes + i)->remaining_time > 0){
				total_tickets = total_tickets + (processes + i)->tickets;
			}
		}

		if (total_tickets > 0){
			int ticket_counter = 0;
			int winning_ticket = rand() % total_tickets; 

			for(int i = 0; i < num_processes; i++){
				if ((processes + i)->arrival_time <= current_time && (processes + i)->remaining_time > 0){
					ticket_counter = ticket_counter + (processes + i)->tickets;
				}

				if (ticket_counter > winning_ticket){
					current_process = processes + i;
					break;
				}
			}
		} else current_process = NULL;
	
		if (current_process != NULL){
			if (current_process->remaining_time == current_process->burst_time){
				current_process->start_time = current_time;
			}
			//printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);
			current_process->remaining_time--;

			if (current_process->remaining_time == 0){
				current_process->completion_time = current_time;
				//printf("[Time : %d] Process %d is now over.\n", current_time, current_process->pid);

                current_process->response_time = current_process->start_time - current_process->arrival_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;

                //printf("-----> turnaround time : %d, response time : %d\n\n", current_process->turnaround_time, current_process->response_time);

				completed_processes++;
				current_process = NULL;
			}
		} //else printf("[Time : %d] CPU is idle.\n", current_time);

		render_process(current_time, current_process, num_processes);
		current_time++;
		sleep(1);
	}

	display_summary(processes, num_processes);
	printf("\nLottery scheduling simulation successfully completed !\n");
}
