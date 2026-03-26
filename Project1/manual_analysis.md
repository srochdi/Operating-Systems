# Part A - Manual Scheduling Analysis
## CSC 4210 - CPU Scheduling Project

---

## Test Case Data
```
Process  Arrival  Burst  Priority
P1       0        5      2
P2       1        3      1
P3       3        2      2
P4       3        2      2
```

---

## Algorithm 1: FCFS (First-Come, First-Served)

### Gantt Chart
```
|  P1   |  P1   |  P1   |  P1   |  P1   |  P2   |  P2   |  P2   |  P3   |  P3   |  P4   |  P4   |
0       1       2       3       4       5       6       7       8       9       10      11      12
```

### Timeline Breakdown
- **Time 0-5**: P1 runs (arrived at 0, burst=5)
- **Time 5-8**: P2 runs (arrived at 1, burst=3)
- **Time 8-10**: P3 runs (arrived at 3, burst=2)
- **Time 10-12**: P4 runs (arrived at 3, burst=2)

### Calculations

**P1:**
- Arrival: 0, Completion: 5
- Turnaround = 5 - 0 = 5
- Waiting = 5 - 5 = 0
- Response = 0 - 0 = 0

**P2:**
- Arrival: 1, Completion: 8
- Turnaround = 8 - 1 = 7
- Waiting = 7 - 3 = 4
- Response = 5 - 1 = 4

**P3:**
- Arrival: 3, Completion: 10
- Turnaround = 10 - 3 = 7
- Waiting = 7 - 2 = 5
- Response = 8 - 3 = 5

**P4:**
- Arrival: 3, Completion: 12
- Turnaround = 12 - 3 = 9
- Waiting = 9 - 2 = 7
- Response = 10 - 3 = 7

### Averages
- **Average Turnaround Time**: (5 + 7 + 7 + 9) / 4 = **7.0**
- **Average Waiting Time**: (0 + 4 + 5 + 7) / 4 = **4.0**
- **Average Response Time**: (0 + 4 + 5 + 7) / 4 = **4.0**

### Preemption Events
**None** - FCFS is non-preemptive

---

## Algorithm 2: SRTF (Shortest Remaining Time First)

### Gantt Chart
```
|  P1   |  P2   |  P2   |  P2   |  P3   |  P3   |  P4   |  P4   |  P1   |  P1   |  P1   |  P1   |
0       1       2       3       4       5       6       7       8       9       10      11      12
```

### Timeline Breakdown
- **Time 0-1**: P1 runs (rem=5, no competition)
- **Time 1**: P2 arrives (rem=3), preempts P1 (rem=4) → P2 has shorter remaining time
- **Time 1-4**: P2 runs (rem=3)
- **Time 3**: P3 and P4 arrive (rem=2 each), but P2 (rem=1) is shorter
- **Time 4-6**: P3 runs (rem=2, shortest among ready)
- **Time 6-8**: P4 runs (rem=2)
- **Time 8-12**: P1 runs (rem=4, only process left)

### Preemption Events
1. **Time 1**: P1 → P2 (P2's rem=3 < P1's rem=4)

### Calculations

**P1:**
- Arrival: 0, Start: 0, Completion: 12
- Turnaround = 12 - 0 = 12
- Waiting = 12 - 5 = 7
- Response = 0 - 0 = 0

**P2:**
- Arrival: 1, Start: 1, Completion: 4
- Turnaround = 4 - 1 = 3
- Waiting = 3 - 3 = 0
- Response = 1 - 1 = 0

**P3:**
- Arrival: 3, Start: 4, Completion: 6
- Turnaround = 6 - 3 = 3
- Waiting = 3 - 2 = 1
- Response = 4 - 3 = 1

**P4:**
- Arrival: 3, Start: 6, Completion: 8
- Turnaround = 8 - 3 = 5
- Waiting = 5 - 2 = 3
- Response = 6 - 3 = 3

### Averages
- **Average Turnaround Time**: (12 + 3 + 3 + 5) / 4 = **5.75**
- **Average Waiting Time**: (7 + 0 + 1 + 3) / 4 = **2.75**
- **Average Response Time**: (0 + 0 + 1 + 3) / 4 = **1.0**

---

## Algorithm 3: Priority Scheduling (Non-Preemptive)

**Lower number = Higher priority**

### Gantt Chart
```
|  P1   |  P1   |  P1   |  P1   |  P1   |  P2   |  P2   |  P2   |  P3   |  P3   |  P4   |  P4   |
0       1       2       3       4       5       6       7       8       9       10      11      12
```

### Timeline Breakdown
- **Time 0-5**: P1 runs (only process, priority=2)
- **Time 5-8**: P2 runs (priority=1, highest among ready: P2, P3, P4)
- **Time 8-10**: P3 runs (priority=2, P3 arrived before P4)
- **Time 10-12**: P4 runs (priority=2)

### Calculations

**P1:**
- Arrival: 0, Completion: 5
- Turnaround = 5 - 0 = 5
- Waiting = 5 - 5 = 0
- Response = 0 - 0 = 0

**P2:**
- Arrival: 1, Completion: 8
- Turnaround = 8 - 1 = 7
- Waiting = 7 - 3 = 4
- Response = 5 - 1 = 4

**P3:**
- Arrival: 3, Completion: 10
- Turnaround = 10 - 3 = 7
- Waiting = 7 - 2 = 5
- Response = 8 - 3 = 5

**P4:**
- Arrival: 3, Completion: 12
- Turnaround = 12 - 3 = 9
- Waiting = 9 - 2 = 7
- Response = 10 - 3 = 7

### Averages
- **Average Turnaround Time**: (5 + 7 + 7 + 9) / 4 = **7.0**
- **Average Waiting Time**: (0 + 4 + 5 + 7) / 4 = **4.0**
- **Average Response Time**: (0 + 4 + 5 + 7) / 4 = **4.0**

### Preemption Events
**None** - Priority scheduling (non-preemptive) does not preempt

---

## Algorithm 4: Round Robin (Time Quantum = 2)

### Gantt Chart
```
|  P1   |  P1   |  P2   |  P2   |  P1   |  P1   |  P3   |  P3   |  P4   |  P4   |  P2   |  P1   |
0       1       2       3       4       5       6       7       8       9       10      11      12
```

### Timeline Breakdown
- **Time 0-2**: P1 runs for quantum (2 units)
- **Time 2**: P1 preempted (quantum expired), moved to back of queue
- **Time 2-4**: P2 runs for quantum (2 units)
- **Time 4**: P2 preempted (quantum expired), P2 has rem=1
- **Time 4-6**: P1 runs for quantum (2 units)
- **Time 6**: P1 preempted (quantum expired), P1 has rem=1
- **Time 6-8**: P3 runs (completes in 2 units)
- **Time 8-10**: P4 runs (completes in 2 units)
- **Time 10-11**: P2 runs (completes in 1 unit)
- **Time 11-12**: P1 runs (completes in 1 unit)

### Preemption Events
1. **Time 2**: P1 → P2 (quantum expired)
2. **Time 4**: P2 → P1 (quantum expired)
3. **Time 6**: P1 → P3 (quantum expired)

### Calculations

**P1:**
- Arrival: 0, Start: 0, Completion: 12
- Turnaround = 12 - 0 = 12
- Waiting = 12 - 5 = 7
- Response = 0 - 0 = 0

**P2:**
- Arrival: 1, Start: 2, Completion: 11
- Turnaround = 11 - 1 = 10
- Waiting = 10 - 3 = 7
- Response = 2 - 1 = 1

**P3:**
- Arrival: 3, Start: 6, Completion: 8
- Turnaround = 8 - 3 = 5
- Waiting = 5 - 2 = 3
- Response = 6 - 3 = 3

**P4:**
- Arrival: 3, Start: 8, Completion: 10
- Turnaround = 10 - 3 = 7
- Waiting = 7 - 2 = 5
- Response = 8 - 3 = 5

### Averages
- **Average Turnaround Time**: (12 + 10 + 5 + 7) / 4 = **8.5**
- **Average Waiting Time**: (7 + 7 + 3 + 5) / 4 = **5.5**
- **Average Response Time**: (0 + 1 + 3 + 5) / 4 = **2.25**

---

## Summary Comparison

| Algorithm | Avg Turnaround | Avg Waiting | Avg Response |
|-----------|----------------|-------------|--------------|
| FCFS      | 7.0            | 4.0         | 4.0          |
| SRTF      | 5.75           | 2.75        | 1.0          |
| Priority  | 7.0            | 4.0         | 4.0          |
| Round Robin (q=2) | 8.5    | 5.5         | 2.25         |

### Analysis
- **SRTF** provides the best average turnaround and waiting times due to its optimal scheduling
- **SRTF** also has the best response time (1.0)
- **Round Robin** provides fair CPU distribution but has higher turnaround time
- **FCFS and Priority** perform identically for this test case (P1 blocks other processes regardless)
- **Priority scheduling** would differ if P2 (highest priority) arrived earlier

### Preemption Summary
- **FCFS**: 0 preemptions (non-preemptive)
- **SRTF**: 1 preemption (event-based)
- **Priority**: 0 preemptions (non-preemptive)
- **Round Robin**: 3 preemptions (time-based)