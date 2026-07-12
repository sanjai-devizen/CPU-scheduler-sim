#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include "../include/queue.h"
#include "../include/scheduler.h"
#include "../include/display.h"

void simulate_fcfs(process_t* processes, int num_process){
    queue_t* ready_queue = queue_init(); 
    
    unsigned int current_time = 0;
    int completed_processes = 0;
    process_t* current_process = NULL;
    printf("\n----Starting FCFS simulation----\n");
	init_display(num_process);

    while(completed_processes < num_process){
        for(unsigned int i = 0; i < (unsigned)num_process; i++){
            if ((processes + i)->arrival_time == current_time){
                queue_enqueue(ready_queue, processes + i);
                //printf("[Time : %d] Process %d loaded into queue.\n", current_time, (processes + i)->pid);
            }
        }

        if (current_process == NULL && !queue_is_empty(ready_queue)){
            queue_dequeue(ready_queue, &current_process);
            current_process->start_time = current_time;
        }

        if (current_process != NULL){
            //printf("[Time : %d] Process %d is running. (time left : %d)\n", current_time, current_process->pid, current_process->remaining_time);
            
            current_process->remaining_time--;

            if (current_process->remaining_time == 0){
                current_process->completion_time = current_time + 1;
                //printf("[Time : %d] Process %d is done.\n", current_time + 1, current_process->pid);

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
    free(ready_queue); 
    printf("\nFCFS simulation complete\n");
}