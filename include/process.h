#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
	unsigned int pid;
	unsigned int arrival_time;
	unsigned int burst_time;
	unsigned int remaining_time;
	unsigned int start_time;
	unsigned int completion_time;

	//MLFQ specific
	unsigned int priority;
	unsigned int remaining_allotment;

	//lottery specific
	unsigned int tickets;

	//stride specific
	unsigned int stride;
	unsigned int pass;

	//analysis
	unsigned int turnaround_time;
	unsigned int response_time;
} process_t;

#endif
