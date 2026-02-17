#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// Process Control Block structure
struct PCB {
    int pid;
    int arrival_time;
    int total_burst_time;
    int remaining_time;
    int priority;
    string state;  // NEW, READY, RUNNING, TERMINATED
    int start_time;
    int completion_time;
    
    PCB(int p, int arr, int burst, int prio) {
        pid = p;
        arrival_time = arr;
        total_burst_time = burst;
        remaining_time = burst;
        priority = prio;
        state = "NEW";
        start_time = -1;
        completion_time = -1;
    }
};

class CPUScheduler {
private:
    vector<PCB> processes;
    int current_time;
    int time_quantum; // for Round Robin
    
    void printTimeUnit(int time, PCB* running, vector<PCB*> ready_queue) {
        cout << "Time " << time << ":" << endl << endl;
        
        if (running != nullptr) {
            cout << "RUNNING:" << endl;
            cout << "PID=" << running->pid 
                 << "  Arr=" << running->arrival_time
                 << "  Burst=" << running->total_burst_time
                 << "  Rem=" << running->remaining_time
                 << "  Prio=" << running->priority
                 << "  State=" << running->state << endl << endl;
        } else {
            cout << "RUNNING: IDLE" << endl << endl;
        }
        
        if (!ready_queue.empty()) {
            cout << "READY:" << endl;
            for (auto pcb : ready_queue) {
                cout << "PID=" << pcb->pid 
                     << "  Arr=" << pcb->arrival_time
                     << "  Burst=" << pcb->total_burst_time
                     << "  Rem=" << pcb->remaining_time
                     << "  Prio=" << pcb->priority
                     << "  State=" << pcb->state << endl;
            }
            cout << endl;
        }
    }
    
public:
    CPUScheduler(int quantum = 2) : current_time(0), time_quantum(quantum) {}
    
    void addProcess(int pid, int arrival, int burst, int priority) {
        processes.push_back(PCB(pid, arrival, burst, priority));
    }
    
    // FCFS Scheduling (non-preemptive)
    void scheduleFCFS() {
        cout << "========================================" << endl;
        cout << "FCFS Scheduling" << endl;
        cout << "========================================" << endl << endl;
        
        vector<PCB> procs = processes;
        sort(procs.begin(), procs.end(), [](const PCB& a, const PCB& b) {
            return a.arrival_time < b.arrival_time;
        });
        
        queue<PCB*> ready_queue;
        PCB* running = nullptr;
        int completed = 0;
        current_time = 0;
        
        while (completed < procs.size()) {
            // Admit new arrivals
            for (auto& p : procs) {
                if (p.arrival_time == current_time && p.state == "NEW") {
                    p.state = "READY";
                    ready_queue.push(&p);
                }
            }
            
            // If no process running and queue has processes, schedule next
            if (running == nullptr && !ready_queue.empty()) {
                running = ready_queue.front();
                ready_queue.pop();
                running->state = "RUNNING";
                if (running->start_time == -1) {
                    running->start_time = current_time;
                }
            }
            
            // Print current state
            vector<PCB*> ready_vec;
            queue<PCB*> temp_queue = ready_queue;
            while (!temp_queue.empty()) {
                ready_vec.push_back(temp_queue.front());
                temp_queue.pop();
            }
            printTimeUnit(current_time, running, ready_vec);
            
            // Execute running process
            if (running != nullptr) {
                running->remaining_time--;
                
                // Check if process completed
                if (running->remaining_time == 0) {
                    running->state = "TERMINATED";
                    running->completion_time = current_time + 1;
                    completed++;
                    running = nullptr;
                }
            }
            
            current_time++;
        }
        
        printMetrics(procs);
    }
    
    // SRTF Scheduling (preemptive, event-based)
    void scheduleSRTF() {
        cout << "========================================" << endl;
        cout << "SRTF Scheduling" << endl;
        cout << "========================================" << endl << endl;
        
        vector<PCB> procs = processes;
        vector<PCB*> ready_queue;
        PCB* running = nullptr;
        int completed = 0;
        current_time = 0;
        
        while (completed < procs.size()) {
            // Admit new arrivals
            for (auto& p : procs) {
                if (p.arrival_time == current_time && p.state == "NEW") {
                    p.state = "READY";
                    ready_queue.push_back(&p);
                }
            }
            
            // Check for preemption (SRTF - preempt if shorter job arrives)
            if (running != nullptr && !ready_queue.empty()) {
                auto shortest = min_element(ready_queue.begin(), ready_queue.end(),
                    [](PCB* a, PCB* b) { return a->remaining_time < b->remaining_time; });
                
                if ((*shortest)->remaining_time < running->remaining_time) {
                    running->state = "READY";
                    ready_queue.push_back(running);
                    running = nullptr;
                }
            }
            
            // If no process running and queue has processes, schedule shortest
            if (running == nullptr && !ready_queue.empty()) {
                auto shortest = min_element(ready_queue.begin(), ready_queue.end(),
                    [](PCB* a, PCB* b) { return a->remaining_time < b->remaining_time; });
                running = *shortest;
                ready_queue.erase(shortest);
                running->state = "RUNNING";
                if (running->start_time == -1) {
                    running->start_time = current_time;
                }
            }
            
            // Sort ready queue by remaining time for display
            sort(ready_queue.begin(), ready_queue.end(),
                [](PCB* a, PCB* b) { return a->remaining_time < b->remaining_time; });
            
            printTimeUnit(current_time, running, ready_queue);
            
            // Execute running process
            if (running != nullptr) {
                running->remaining_time--;
                
                if (running->remaining_time == 0) {
                    running->state = "TERMINATED";
                    running->completion_time = current_time + 1;
                    completed++;
                    running = nullptr;
                }
            }
            
            current_time++;
        }
        
        printMetrics(procs);
    }
    
    // Priority Scheduling (non-preemptive)
    void schedulePriority() {
        cout << "========================================" << endl;
        cout << "Priority Scheduling (Non-Preemptive)" << endl;
        cout << "========================================" << endl << endl;
        
        vector<PCB> procs = processes;
        vector<PCB*> ready_queue;
        PCB* running = nullptr;
        int completed = 0;
        current_time = 0;
        
        while (completed < procs.size()) {
            // Admit new arrivals
            for (auto& p : procs) {
                if (p.arrival_time == current_time && p.state == "NEW") {
                    p.state = "READY";
                    ready_queue.push_back(&p);
                }
            }
            
            // If no process running and queue has processes, schedule highest priority
            if (running == nullptr && !ready_queue.empty()) {
                auto highest = min_element(ready_queue.begin(), ready_queue.end(),
                    [](PCB* a, PCB* b) { return a->priority < b->priority; });
                running = *highest;
                ready_queue.erase(highest);
                running->state = "RUNNING";
                if (running->start_time == -1) {
                    running->start_time = current_time;
                }
            }
            
            // Sort ready queue by priority for display
            sort(ready_queue.begin(), ready_queue.end(),
                [](PCB* a, PCB* b) { return a->priority < b->priority; });
            
            printTimeUnit(current_time, running, ready_queue);
            
            // Execute running process
            if (running != nullptr) {
                running->remaining_time--;
                
                if (running->remaining_time == 0) {
                    running->state = "TERMINATED";
                    running->completion_time = current_time + 1;
                    completed++;
                    running = nullptr;
                }
            }
            
            current_time++;
        }
        
        printMetrics(procs);
    }
    
    // Round Robin Scheduling (preemptive, time-based)
    void scheduleRoundRobin() {
        cout << "========================================" << endl;
        cout << "Round Robin Scheduling (Quantum=" << time_quantum << ")" << endl;
        cout << "========================================" << endl << endl;
        
        vector<PCB> procs = processes;
        queue<PCB*> ready_queue;
        PCB* running = nullptr;
        int completed = 0;
        current_time = 0;
        int quantum_used = 0;
        
        while (completed < procs.size()) {
            // Admit new arrivals
            for (auto& p : procs) {
                if (p.arrival_time == current_time && p.state == "NEW") {
                    p.state = "READY";
                    ready_queue.push(&p);
                }
            }
            
            // Check if quantum expired
            if (running != nullptr && quantum_used >= time_quantum) {
                running->state = "READY";
                ready_queue.push(running);
                running = nullptr;
                quantum_used = 0;
            }
            
            // If no process running and queue has processes, schedule next
            if (running == nullptr && !ready_queue.empty()) {
                running = ready_queue.front();
                ready_queue.pop();
                running->state = "RUNNING";
                quantum_used = 0;
                if (running->start_time == -1) {
                    running->start_time = current_time;
                }
            }
            
            // Convert queue to vector for printing
            vector<PCB*> ready_vec;
            queue<PCB*> temp_queue = ready_queue;
            while (!temp_queue.empty()) {
                ready_vec.push_back(temp_queue.front());
                temp_queue.pop();
            }
            
            printTimeUnit(current_time, running, ready_vec);
            
            // Execute running process
            if (running != nullptr) {
                running->remaining_time--;
                quantum_used++;
                
                if (running->remaining_time == 0) {
                    running->state = "TERMINATED";
                    running->completion_time = current_time + 1;
                    completed++;
                    running = nullptr;
                    quantum_used = 0;
                }
            }
            
            current_time++;
        }
        
        printMetrics(procs);
    }
    
    void printMetrics(const vector<PCB>& procs) {
        cout << endl << "========================================" << endl;
        cout << "Performance Metrics" << endl;
        cout << "========================================" << endl;
        
        double total_turnaround = 0;
        double total_waiting = 0;
        double total_response = 0;
        
        for (const auto& p : procs) {
            int turnaround = p.completion_time - p.arrival_time;
            int waiting = turnaround - p.total_burst_time;
            int response = p.start_time - p.arrival_time;
            
            cout << "PID " << p.pid << ": "
                 << "Turnaround=" << turnaround
                 << ", Waiting=" << waiting
                 << ", Response=" << response << endl;
            
            total_turnaround += turnaround;
            total_waiting += waiting;
            total_response += response;
        }
        
        cout << endl << "Average Turnaround Time: " << total_turnaround / procs.size() << endl;
        cout << "Average Waiting Time: " << total_waiting / procs.size() << endl;
        cout << "Average Response Time: " << total_response / procs.size() << endl;
        cout << endl;
    }
    
    void resetProcesses() {
        for (auto& p : processes) {
            p.remaining_time = p.total_burst_time;
            p.state = "NEW";
            p.start_time = -1;
            p.completion_time = -1;
        }
        current_time = 0;
    }
};

int main() {
    // Example test case - you can modify this or read from file
    CPUScheduler scheduler(2); // quantum = 2 for Round Robin
    
    // Add processes: (PID, Arrival, Burst, Priority)
    scheduler.addProcess(1, 0, 5, 2);
    scheduler.addProcess(2, 1, 3, 1);
    scheduler.addProcess(3, 3, 2, 2);
    scheduler.addProcess(4, 3, 2, 2);
    
    // Run all scheduling algorithms
    scheduler.scheduleFCFS();
    cout << "\n\n";
    
    scheduler.resetProcesses();
    scheduler.scheduleSRTF();
    cout << "\n\n";
    
    scheduler.resetProcesses();
    scheduler.schedulePriority();
    cout << "\n\n";
    
    scheduler.resetProcesses();
    scheduler.scheduleRoundRobin();
    
    return 0;
}