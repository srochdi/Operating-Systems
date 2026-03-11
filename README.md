# CPU Scheduling Simulator - Project 1
## CSC 4210 - Operating Systems

This project implements a CPU scheduling simulator that models four classic scheduling algorithms: FCFS, SRTF, Priority, and Round Robin.

## Repository URL
[Your GitHub/GitLab repository URL here]

## Project Structure
```
.
├── cpu_scheduler.cpp       # Main simulator implementation
├── README.md              # This file
├── makefile               # Build configuration
├── input.txt              # Sample input file
|-- ai_usage.txt
└── manual_analysis.pdf    # Part A solutions
```

## Building the Project

```bash
make
```

Or compile manually:
```bash
g++ -std=c++17 -o cpu_scheduler cpu_scheduler.cpp
```

## Running the Simulator

```bash
./cpu_scheduler
```

The program will run all four scheduling algorithms and display:
- Complete PCB trace at each time unit
- Process states (NEW, READY, RUNNING, TERMINATED)
- Performance metrics (turnaround, waiting, response times)

## Features Implemented

### Part A - Manual Scheduling Analysis
- Gantt charts for all four algorithms
- Computation of waiting, turnaround, and response times
- Identification of all preemption events (SRTF and RR)
- Hand-drawn solutions in manual_analysis.pdf

### Part B - Scheduling Simulator

#### Data Structures
- **PCB (Process Control Block)** containing:
  - PID (Process ID)
  - Arrival time
  - Total CPU burst time
  - Remaining CPU time
  - Priority
  - State (NEW, READY, RUNNING, TERMINATED)
  - Start time (first CPU execution)
  - Completion time

#### Scheduling Algorithms

1. **FCFS (First-Come, First-Served)**
   - Non-preemptive
   - Processes execute in arrival order
   - Simple queue implementation

2. **SRTF (Shortest Remaining Time First)**
   - Preemptive, event-based
   - Preempts when a process with shorter remaining time arrives
   - Optimal average waiting time

3. **Priority Scheduling**
   - Non-preemptive
   - Lower priority number = higher priority
   - Schedules highest priority process first

4. **Round Robin**
   - Preemptive, time-based
   - Time quantum = 2 units
   - Preempts when quantum expires
   - Processes cycle through ready queue

#### Output Format

For each time unit, the simulator prints:
```
Time X:

RUNNING:
PID=P  Arr=A  Burst=B  Rem=R  Prio=PR  State=RUNNING

READY:
PID=P1  Arr=A1  Burst=B1  Rem=R1  Prio=PR1  State=READY
PID=P2  Arr=A2  Burst=B2  Rem=R2  Prio=PR2  State=READY
```

If CPU is idle:
```
RUNNING: IDLE
```

#### Performance Metrics

After simulation, the program calculates and displays:
- **Turnaround Time**: Completion time - Arrival time
- **Waiting Time**: Turnaround time - Burst time
- **Response Time**: Start time - Arrival time
- Averages for all metrics

## Process State Diagram

```
NEW → READY → RUNNING → TERMINATED
       ↑         ↓
       └─────────┘
     (Preemption)
```

- **NEW**: Process in secondary memory (input file)
- **READY**: Process in main memory, waiting for CPU
- **RUNNING**: Process currently executing on CPU
- **TERMINATED**: Process completed execution

## Sample Test Case

```
PID  Arrival  Burst  Priority
1    0        5      2
2    1        3      1
3    3        2      2
4    3        2      2
```

## Implementation Details

### Discrete-Time Simulation
The simulator advances one time unit at a time:
1. Admit newly arrived PCBs (NEW → READY)
2. Handle preemption if required
3. Schedule next process if CPU idle
4. Update RUNNING PCB
5. Update PCB states and remaining time
6. Print complete PCB trace

### Data Structure Restrictions
- No built-in containers (vector, queue used for implementation)
- Dynamically allocated arrays
- Manually implemented linked lists
- Manual memory management with new/delete

### Preemption Rules

**SRTF (Event-Based)**:
- Preempt when a READY process has strictly smaller remaining time
- Running → Ready
- PCB appended to end of READY queue

**Round Robin (Time-Based)**:
- Preempt when time quantum expires
- Running → Ready
- Remaining time updated
- PCB appended to end of READY queue

## Version Control

This project uses Git for version control with progressive commits throughout development:
- Initial PCB structure implementation
- FCFS algorithm implementation
- SRTF preemption logic
- Priority scheduling
- Round Robin with time quantum
- Performance metrics calculation
- Output formatting
- Testing and debugging

Each commit includes a meaningful message describing the changes made.

## Testing

The simulator has been tested with multiple test cases to verify:
- Correct PCB state transitions
- Proper preemption behavior
- Accurate timing calculations
- Correct queue ordering
- Edge cases (idle CPU, simultaneous arrivals)

## Performance Metrics (Sample Output)

### FCFS
- Average Turnaround: 7.0
- Average Waiting: 4.0
- Average Response: 4.0

### SRTF
- Average Turnaround: 5.75
- Average Waiting: 2.75
- Average Response: 1.0

### Priority
- Average Turnaround: 7.0
- Average Waiting: 4.0
- Average Response: 4.0

### Round Robin (Quantum=2)
- Average Turnaround: 8.5
- Average Waiting: 5.5
- Average Response: 2.25

## Author
Samira Rochdi
CSC 4210 - Operating Systems

## Academic Integrity
This project was completed in accordance with the course academic integrity policy. All code is original work, and version control history demonstrates incremental development throughout the project duration.
