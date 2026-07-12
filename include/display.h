#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

void init_display(int num_process);
void render_process(int current_time, process_t* current_process, int num_process);
void display_summary(process_t* processes, int num_process);

#endif