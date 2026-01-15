# Operating Systems Toolkit (C)

This repository contains implementations of core Operating Systems concepts written in **C**.  
The project focuses on understanding how an operating system schedules processes and avoids deadlock using well-known algorithms.

 CPU Scheduling Simulator

This module implements the following CPU scheduling algorithms:

- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling (Non-preemptive)
- Round Robin

Features
- Menu-driven program
- User-defined number of processes
- User-defined arrival time, burst time, priority, and time quantum
- Calculates:
  - Waiting Time
  - Turnaround Time
  - Average Waiting Time
  - Average Turnaround Time
- Displays execution order of processes

Deadlock Avoidance – Banker’s Algorithm

This module implements **Banker’s Algorithm** to determine whether a system is in a safe or unsafe state.

 Features
- User input for:
  - Number of processes
  - Number of resource types
  - Allocation matrix
  - Maximum requirement matrix
  - Available resources
- Calculates the **Need matrix**
- Determines:
  - Safe state or Deadlock
  - Safe sequence (if it exists)


How to Run

The programs can be compiled and executed using any standard C compiler.

CPU Scheduling

Alternatively, the programs can be executed using an online C compiler.

 Concepts Covered

- CPU Scheduling Algorithms
- Process Management
- Deadlock Avoidance
- Resource Allocation
- Operating Systems Fundamentals



Author
Abhigna Gajendra  
Computer Science Engineering Student
