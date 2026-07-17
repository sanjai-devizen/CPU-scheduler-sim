# 🖥️ CPU Scheduling Engine

![Status: Completed](https://img.shields.io/badge/Status-Completed-orange?style=for-the-badge)
![Language: C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![System: Linux](https://img.shields.io/badge/System-Linux-blue?style=for-the-badge)

An educational CPU scheduling simulator designed to mimic real-time process scheduling. By slowing down execution to a human-readable pace, it provides a clear understanding of how core OS algorithms function under the hood. Written entirely in pure C with zero external dependencies and dynamic memory management.

## ⚙️ Project Roadmap & Algorithms

### Phase 1: Core Single-Core Scheduling (Completed)
- [x] **FCFS** (First-Come, First-Served)
- [x] **SJF** (Shortest Job First - Non-preemptive)
- [x] **STCF** (Shortest Time-to-Completion First - Preemptive)
- [x] **RR** (Round Robin)
- [x] **MLFQ** (Multi-Level Feedback Queue with global priority boosting and anti-starvation)

### Phase 2: Proportional Share & Metrics (Upcoming)
- [x] **Lottery Scheduling** (Randomized ticket-based proportional share)
- [x] **Stride Scheduling** (Deterministic proportional share)
- [x] **Simple display of process runtime and metrics** (Inspired from Gantt chart analysis to benchmark turnaround/response times across all algorithms)

## 🚀 Quick Start

Compile the engine and launch the interactive terminal menu:
```bash
$ make
$ make run
```

## Terminal display design

### Prompt

<img width="1862" height="564" alt="Screenshot From 2026-07-17 10-33-07" src="https://github.com/user-attachments/assets/545074a6-804d-4ccf-8aa8-7af1989b316f" />

### Terminal Display

<img width="1822" height="1003" alt="Screenshot From 2026-07-17 10-36-21" src="https://github.com/user-attachments/assets/2fa41b8c-2bfa-4094-89de-45af13afc9dd" />

## Code review 

While the current simulator compiles and runs flawlessly, there is still room to expand how process runtimes and metric summaries are visualized. Currently, display.c renders foundational blocks and analytics to track active processes. However, advanced algorithms like MLFQ and Round Robin will eventually require a more intricate rendering engine to accurately visualize rapid context switches and queue-level priority boosts. The core engine is complete, but future updates will focus on building specialized, algorithm-specific terminal displays.
