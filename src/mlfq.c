#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/queue.h"
#include "../include/scheduler.h"

#define BOOST_INTERVAL 10
#define NUM_QUEUES 3

const unsigned int TIME_QUANTUM[NUM_QUEUES] = {2, 4, 8};

void simulate_mlfq(process_t* processes, int num_process){
	queue_t* mlfq_queues[NUM_QUEUES];
	for(int i = 0; i < NUM_QUEUES; i++){
		mlfq_queues[i] = queue_init();
		if (mlfq_queues[i] == NULL){
			printf("Fatal Error: Failed to initialize queues !\n");
			return;
		}
	}

	unsigned int current_time = 0;
	int completed_processes = 0;
	process_t* current_process = NULL;

	printf("\n----Starting 3-level MLFQ scheduling----\n\n");
	while(completed_processes < num_process){
		if (current_time > 0 && current_time % BOOST_INTERVAL == 0){
			printf("[Time : %d] === GLOBAL PRIORITY BOOST ===\n", current_time);

			if (current_process != NULL){
				current_process->priority = NUM_QUEUES - 1;
				current_process->remaining_allotment = TIME_QUANTUM[NUM_QUEUES - 1];
			}

			for(int i = NUM_QUEUES - 2; i >= 0; i--){
				while(!queue_is_empty(mlfq_queues[i])){
					process_t* p_upgrade = NULL;
					queue_dequeue(mlfq_queues[i], &p_upgrade);
					if (p_upgrade != NULL){
						p_upgrade->priority = NUM_QUEUES - 1;
						p_upgrade->remaining_allotment = TIME_QUANTUM[NUM_QUEUES - 1];
						queue_enqueue(mlfq_queues[NUM_QUEUES - 1], p_upgrade);							
					}
				}	
			}
		}

		for(int i = 0; i < num_process; i++){
			if ((processes + i)->arrival_time == current_time){
				process_t* p = processes + i;
				p->priority = NUM_QUEUES - 1;
				p->remaining_allotment = TIME_QUANTUM[NUM_QUEUES - 1];
				queue_enqueue(mlfq_queues[NUM_QUEUES - 1], p);			
			}
		}

		if (current_process == NULL){
			for (int q = NUM_QUEUES - 1; q >= 0; q--) {
			    if (!queue_is_empty(mlfq_queues[q])) {
			        queue_dequeue(mlfq_queues[q], &current_process);
			        
			        if (current_process->remaining_time == current_process->burst_time) {
			            current_process->start_time = current_time;
			        }
			        break; 
			    }
			}
		}

		if (current_process != NULL){
			printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);
			current_process->remaining_time--;
			current_process->remaining_allotment--;
			current_time++;

			if (current_process->remaining_time == 0){
				current_process->completion_time = current_time;
				printf("[Time : %d] Process %d is now over.\n", current_time, current_process->pid);

                current_process->response_time = current_process->start_time - current_process->arrival_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;

                printf("-----> turnaround time : %d, response time : %d\n\n", current_process->turnaround_time, current_process->response_time);

				completed_processes++;
				current_process = NULL;
			} else if (current_process->remaining_allotment == 0){
				unsigned int old_priority = current_process->priority;

				if (current_process->priority > 0) 
					current_process->priority--;

				current_process->remaining_allotment = TIME_QUANTUM[current_process->priority];
				printf("[Time : %d] Process %d exhausted queue %d's time splice hence demoted !\n", current_time, current_process->pid, old_priority + 1);
				
				queue_enqueue(mlfq_queues[current_process->priority], current_process);
				current_process = NULL;
			} else {
				int higher_jobs = 0;

				for(int q = NUM_QUEUES - 1; q > (int)current_process->priority; --q){
					if (!queue_is_empty(mlfq_queues[q])){
						higher_jobs = 1;
						break;
					}				
				}

				if (higher_jobs){
					printf("[Time : %d] While process %d was running, a process with higher priority was found.\n", current_time, current_process->pid);
					queue_enqueue(mlfq_queues[current_process->priority], current_process);
					current_process = NULL;
				}
			}
		} else {
			printf("[Time : %d] CPU is idle\n", current_time);
			current_time++;
		}

		sleep(1);
	}

	for(int i = 0; i < NUM_QUEUES; i++){
        free(mlfq_queues[i]);
    }

	printf("MLFQ simulation successfully completed !\n");
}
