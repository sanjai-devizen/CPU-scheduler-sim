#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/queue.h"
#include "../include/scheduler.h"

int main(){
	srand(time(NULL));
	char simChoice[10];

	printf("CPU scheduler sim :\n\n");

	int num_processes, pid = 0;
	printf("How many processes do you want to run ? ");
	scanf("%d", &num_processes);

	process_t* processes = (process_t*)malloc(num_processes * sizeof(process_t));

	for(int i = 0; i < num_processes; ++i){
		(processes + i)->pid = ++pid;
		printf("\nArrival time of process %d : ", (processes + i)->pid);
		scanf("%d", &(processes + i)->arrival_time);
		printf("\nLife time of process %d : ", (processes + i)->pid);
		scanf("%d", &(processes + i)->burst_time);
		printf("\nTickets for process %d : ", i + 1);
		scanf("%u", &(processes + i)->tickets);

		(processes + i)->remaining_time = (processes + i)->burst_time;
		(processes + i)->start_time = 0;
		(processes + i)->completion_time = 0;
	}

	printf("Which simulation to run ? (FCFS / SJF / STCF / RR / MLFQ / LOTTERY / STRIDE) : ");
	scanf("%9s", simChoice);
	if (strcmp(simChoice, "FCFS") == 0) simulate_fcfs(processes, num_processes);
	else if (strcmp(simChoice, "SJF") == 0) simulate_sjf(processes, num_processes);
	else if (strcmp(simChoice, "STCF") == 0) simulate_stcf(processes, num_processes);
	else if (strcmp(simChoice, "RR") == 0) simulate_rr(processes, num_processes);
	else if (strcmp(simChoice, "MLFQ") == 0) simulate_mlfq(processes, num_processes);
	else if (strcmp(simChoice, "LOTTERY") == 0) simulate_lottery(processes, num_processes);
	else if (strcmp(simChoice, "STRIDE") == 0) simulate_stride(processes, num_processes);
	else printf("Invalid input !\n");

	free(processes);

	return 0;
}
