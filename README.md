# Z-RTOS-

## Description
I have developed my own Real-Time Operating System (RTOS) from scratch, designed to work with various processors/MCUs.<br />
The purpose of **ZRTOS** is to make the System capable of multitasking. It offers fundamental RTOS features.

## Features
- **Task Management**: Manage multiple tasks with different priorities.
- **Priority Based RTOS**: Highest Priority Task Runs First.
- **Round-Robin Support**: Support Round-Robin Scheduling when two or more tasks have the same highest priority.
- **sleep mode**: Executes a power-efficient function when the system goes into the IDLE state.
- **Context Switching**: Monitors and logs context switches with an optional hook function.
- **Mutex Support**: Provides a locking mechanism to ensure that resources are accessed mutually exclusively. Helpful for synchronization.
## Repo / Project Structure
```bash
$ Z-RTOS
.
├── Case Studies
│   ├── CaseStudy 1                  --> **Task Delaying** Implementation with Power efficient IDLE State.  
│   ├── CaseStudy 2                  --> **Round-Robin** Implementation with priority based Algorithm.
│   ├── CaseStudy 3                  --> **Acquire mutex* Implementation.
│   └── CaseStudy 4                  --> **DeadLock** Implementation.
├── inc
│   ├── CortexMX_OS_porting.h        --> Is Used to Port Z-RTOS to different MCUs.
│   ├── Scheduler.h                  --> Supported APIs Prototypes.
│   └── Z_RTOS_FIFO.h                --> QUEUE (FIFO) APIs Prototypes.
├── src
|   ├── CortexMX_OS_porting.c        --> Is Used to define all processor faults as weak fn.
|   ├── Scheduler.c                  --> Supported APIs Definitions.
|   └── Z_RTOS_FIFO.c                --> QUEUE (FIFO) APIs Definitions.
├── Documentation
└── README.md
```

## How-To
## Important Note
This Repo's README.md is under development.
