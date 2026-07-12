#include <stdio.h>
#include "../include/display.h"

#define CLEAR_SCREEN "\033[2J\033[H" 
#define HIDE_CURSOR  "\033[?25l"
#define SHOW_CURSOR  "\033[?25h"

#define WHITE_BLOCK "█████"
#define EMPTY_BLOCK "░░░░░"

void init_display(int num_process){
    printf(CLEAR_SCREEN);
    printf(HIDE_CURSOR);
    
    printf("! SCHEDULING ALGORITHM IN ACTION !\n");

    printf("system time   "); 
    
    for(int i = 0; i < num_process; i++){
        printf("P - %-2d ", i + 1); 
    }
    
    printf("\n"); 
    fflush(stdout);
}

void render_process(int current_time, process_t* current_process, int num_process){
    
    printf("    %04d      ", current_time);

    for(int i = 0; i < num_process; i++){
        
        if (current_process != NULL && current_process->pid == (unsigned)i + 1) {
            printf("%s  ", WHITE_BLOCK); 
        } else {
            printf("%s  ", EMPTY_BLOCK);      
        }
    }

    printf("\n");
    fflush(stdout);
}

void display_summary(process_t* processes, int num_process) {
    int avg_turnaround_time = 0, avg_response_time = 0;
    for(int i = 0; i < num_process; i++){
        printf("\n----> turnaround time of process %d : %d\n", (processes + i)->pid, (processes + i)->turnaround_time);
        avg_turnaround_time = avg_turnaround_time + (processes + i)->turnaround_time;
        printf("----> response time of process %d : %d\n", (processes + i)->pid, (processes + i)->response_time);
        avg_response_time = avg_response_time + (processes + i)->response_time;
    }
    avg_turnaround_time = avg_turnaround_time / num_process;
    avg_response_time = avg_response_time / num_process;

    printf("\n# AVERAGE TURNAROUND TIME : %d\n# AVERAGE RESPONSE TIME : %d\n", avg_turnaround_time, avg_response_time);
    printf(SHOW_CURSOR);
}