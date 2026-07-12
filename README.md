# 🖥️ CPU Scheduling Engine

![Status: Completed](https://img.shields.io/badge/Status-Work%20in%20Progress-orange?style=for-the-badge)
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
