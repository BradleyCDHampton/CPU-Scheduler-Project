/*
    Bradley Hampton 12/3/2023
    CS 471 Old Dominion University

    Class CPUScheduler Represents our CPU Scheduler Simulation.
    Constructor is called with an input file and a comparison mode.
    mode = FCFS, SJF, or PRIORITY representing our three sorting algorithms.

    This class contains two containers, deque arrivals and priority_queue readyQueue.
    arrivals and readyQueue work together to simulate processes entering the ready state and running state.

    CPUScheduler simulates Processes through the new, ready, running, and exit states.
        new state --> ready state        Process is extracted from arrivals and pushed onto readyQueue
        ready state --> running state    runProcess(process, quantum)
        running state --> ready state    runProcess pushes a process that has been preempted back onto readyQueue
        running state --> exit state     runProcess completes without preemption.     

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

// Configuration modes: First-Come-First-Serve, Shortest-Job-First, Priority w/ Preemption
enum mode {FCFS, SJF, PRIORITY};


class CPUScheduler{
    private:
        /* Data for Statistic Calculations */
        int processCount;
        int time;
        int totalIdleTime;
        int sumTurnaround;
        int sumWaitingTime;
        int sumResponseTime;

        int comparisonMode; // Configuration for FCFS, SJF, PRIORITY
                            // Affects how Processes are initialized for comparison.

        class Process; // inner class

        void runProcess(Process);
        void runProcess(Process, int quantum);
        void advanceTime(int cpuBurstCycles);
        void idle(Process);
        void nonPreemptiveSchedule();
        int findNextPreemption(Process);

\
        // where the Processes are stored before they arrive at readyQueue. Is a deque for random-access.
        std::deque<Process> arrivals; 

        // min priority queue. Returns the lowest ArrivalTime, CPU Burst, or Priority... depending on what we're comparing!
        std::priority_queue<Process, std::vector<Process>, std::greater<Process>>  readyQueue;
    

        // Represents a single CPU process.
        // Includes configurations for overridden operator< to compare two processes.
        class Process{
            public:
                int arrivalTime;
                int latestArrivalTime;
                int cpuBurstLength;
                int priority;
                int remainingCPUBurst;
                int comparisonValue;        // for overriden < operator.

                Process(int arrival, int cpu, int prior, int mode){ // move functions to their own section of code?
                    arrivalTime = arrival;
                    latestArrivalTime = arrival;
                    cpuBurstLength = cpu;
                    remainingCPUBurst = cpu;
                    priority = prior;

                    switch(mode){
                        default:
                        case FCFS:      // First Come First Serve
                            comparisonValue = arrival;
                            break;
                        case SJF:       // Shortest Job First
                            comparisonValue = cpu;
                            break;
                        case PRIORITY:  // Priority with Preemption
                            comparisonValue = prior;
                            break;
                    }
                }

                // < operator; invoked implicitly as the comparator for priority_queue readyQueue.
                // i.e. when we call readyQueue.pop(), we return the next process that should be run!
                bool operator>(Process otherProcess) const{
                    return comparisonValue > otherProcess.comparisonValue;
                }
        };

        public:
            CPUScheduler(std::string filename, int mode); // constructor
            void runScheduler();
            bool compareProcesses(Process a, Process b);
            void output(std::string outputFileName); // output 

};

/*
    CPUScheduler Constructor ------------------------------------------------------------
*/

// Creates an object CPUScheduler.
// [Pre-Condition]: filename is a valid filename and mode == FCFS, SJF, or PRIORITY
// [Post-Condition]: CPUScheduler is initialized and configured to FCFS, SJF, or PRIORITY.
CPUScheduler::CPUScheduler(std::string filename, int mode){ 
    
    comparisonMode = mode;    

    //initialize arrival vector
    std::ifstream inputData;
    inputData.open(filename);

    //skip first line
    inputData.ignore(256, '\n'); //replace w/ streamsizemax

    int arr, cpu, prior; // get first input
    inputData >> arr >> cpu >> prior;
    while(inputData){
        arrivals.push_back(Process(arr, cpu, prior, mode));
        inputData >> arr >> cpu >> prior;   
    }

    // sort the arrival queue by arrivalTime
    std::sort(arrivals.begin(), arrivals.end(), [](Process a, Process b)
                                  {
                                      return a.arrivalTime < b.arrivalTime;
                                  });

    inputData.close();

    readyQueue;

    time = 0;
    totalIdleTime = 0;
    sumTurnaround = 0;
    sumWaitingTime = 0;
    sumResponseTime = 0;
    processCount = arrivals.size();
}

/*
    CPUScheduler Public Methods ------------------------------------------------------------
*/

// Runs a simulation for CPUScheduler
// [Pre-Condition]: comparisonMode == FCFS, SJF, or PRIORITY (doesn't matter),
// all Processes in arrivals are initialized according to comparisonMode
// (i.e. process.comparisonValue == process.priority iff comparisonMode == PRIORITY) and etc.
// [Post-Condition]: arrivals and readyQueue are empty; CPUScheduler member variables are updated
// according to the results of the simulation.
void CPUScheduler::runScheduler(){
    while (readyQueue.size() != 0 || arrivals.size() != 0){
        while (readyQueue.size() != 0){
            Process nextProcess = readyQueue.top(); // evaluated according to comparisonMode
            readyQueue.pop();
            if (comparisonMode == PRIORITY){ // a preemptive mode
                int quantum = findNextPreemption(nextProcess); // quantum <- how long nextProcess runs before preemptiion
                runProcess(nextProcess, quantum);
            }
            else // a non-preemptive mode (i.e. FCFS or SJF)
                runProcess(nextProcess);
        } // we've exhausted all processes in readyQueue, but we could still have some queued in arrivals
        if (arrivals.size() != 0){
            Process nextArrival = arrivals.front();
            idle(nextArrival); // will guarentee AT LEAST one process is in the readyQueue
                               //(could be multiple w/ the same arrivalTime as nextProcess)
        }
    }
}

// Outputs run statistics for CPUScheduler.
// [Pre-Condition]: all member variables of CPUScheduler are initialized.
// [Post-Condition]: Calculations for CPUScheduler simulation are output to both console and an outputFile.
void CPUScheduler::output(std::string outputFileName){

    std::ofstream outputFile;
    outputFile.open(outputFileName, std::ofstream::out | std::ofstream::trunc);

    std::cout
        << "\nStatistics for the Run:" << std::endl
        << "  Number of processes: " << processCount << std::endl
        << "  Total elapsed time: " << time << " CPU Burst cycles" << std::endl
        << "  Thoroughput: " << double(processCount)/time << " processes/CPU Burst cycle" << std::endl                                       
        << "  CPU utilization: " << (double(time - totalIdleTime)/time)*100 << "%" << std::endl                              
        << "  Average waiting time: " << double(sumWaitingTime)/(processCount) << " CPU Burst cycles" << std::endl                                        
        << "  Average turnaround time: " << double(sumTurnaround)/processCount << " CPU Burst cycles" << std::endl        // TODO 
        << "  Average response time: " << double(sumResponseTime)/(processCount) << " CPU Burst cycles" << std::endl;

    outputFile // outputs same data to outputFile.
        << "\nStatistics for the Run:" << std::endl
        << "  Number of processes: " << processCount << std::endl
        << "  Total elapsed time: " << time << " CPU Burst cycles" << std::endl
        << "  Thoroughput: " << double(processCount)/time << " processes/CPU Burst cycle" << std::endl                                       
        << "  CPU utilization: " << (double(time - totalIdleTime)/time)*100 << "%" << std::endl                              
        << "  Average waiting time: " << double(sumWaitingTime)/(processCount) << " CPU Burst cycles" << std::endl                                        
        << "  Average turnaround time: " << double(sumTurnaround)/processCount << " CPU Burst cycles" << std::endl        // TODO 
        << "  Average response time: " << double(sumResponseTime)/(processCount) << " CPU Burst cycles" << std::endl;                                
      outputFile.close();
      return;
}

/*
    CPUScheduler Private Methods ------------------------------------------------------------
*/

// Overload of runProcess
// [Precondition]: process has been identified to run without interruption.
// (i.e. either comparisonMode == FCFS or SJF; OR comparisonMode == PRIORITY but no higher priority process
// will arrive before process exits).
// [Post-Condition]: Calls runProcess where argument quantum == process.cpuBurstLength 
void CPUScheduler::runProcess(Process process){
    runProcess(process, process.cpuBurstLength);
    return;
}

// Simulate execution of a single process.
// [Pre-Condition]: If process be preempted, quantum represents the length of time before
// the preemption will occur; in cases without preemption, quantum equals the time until process exits.
// [Post-Condition]: CPUSchedule statistics sumWaitingTime, sumTurnAround, and time are updated accordingly.
// If a process wass preempted, then it is pushed back onto the  and preemptionCount increments.
void CPUScheduler::runProcess(Process process, int quantum){


    process.remainingCPUBurst -= quantum;
    sumWaitingTime += (time - process.latestArrivalTime);

  

    advanceTime(quantum); // Any newly arrived Processes are pushed onto readyQueue.

    if (process.arrivalTime == process.latestArrivalTime) // if this process hadn't been preempted before...
            sumResponseTime += (time - process.arrivalTime);  // our response time is added at this time.

    if (process.remainingCPUBurst > 0){ // If the process is being preempted
        process.latestArrivalTime = time;
        readyQueue.push(process); // Push preempted process back onto readyQueue
        sumResponseTime += (time - process.latestArrivalTime);
    
    }
    else{ // Process has terminated without being prempted.
        sumTurnaround += (time - process.arrivalTime);
    }
}

// Moves time forward by cpuBurstCycles, then migrates Processes from arrivals to readyQueue as needed.
// [Post-condition]: time is moved forward the amount of cpuBurstCycles specified
// any Processes in arrivals where process.arrivalTime < this new time
// are removed from arrivals and added to readyQueue.
void CPUScheduler::advanceTime(int cpuBurstCycles){
    time += cpuBurstCycles;

    // migrate any processes in arrivals that have arrived to readyQueue.
    while (!arrivals.empty() && arrivals.front().arrivalTime <= time){ 
        
        readyQueue.push(arrivals.front());
        arrivals.pop_front();
    }       
    return;
}

// If neccessary, advances time to the next Process to arrive; increment totalIdleTime accordingly.
// [Pre-condition]: nextProcess represents the nextProcess to by run by the Scheduler.
// time may or may not < nextProcess.arrivalTime.
// [Post-condition]: time >= nextProcess.arrivalTime
// if we incremented time, then totalIdleTime was incremented by the same amount.
void CPUScheduler::idle(Process nextProcess){ 
    if (time < nextProcess.arrivalTime){
        totalIdleTime += (nextProcess.arrivalTime - time); // time will pass without process execution!
        advanceTime(nextProcess.arrivalTime - time);
    }
    return;
}

// PRIORITY mode helper function. Determines "quantum" for currentProcess to run for, considering preemptions.
// [Pre-Condition]: currentProcess represents the current process we mean to run.
// Assuming we ran currentProcess at this time, there may be a process in the arrivals
// queue that has a higher priority than currentProcess, and will arrive before currentProcess exits.
// [Post-Condition]: returns an int value repreesenting the amount of CPU burst cycles currentProcess should run for.
// If currentProcess will be preempted by a higher priority process, this value is the time between the preempt and now.
// Otherwise, if currentProcess will not be preempted, this value equals currentProcess' remainingCPUBurst.
int CPUScheduler::findNextPreemption(Process currentProcess){
    int scope = time + currentProcess.remainingCPUBurst;
    // scope represents the time IF currentProcess runs without interruption.

    int x = 0;
    while (x < arrivals.size() && arrivals.at(x).arrivalTime <= scope){
        if (arrivals.at(x).priority < currentProcess.priority){
            // we have found a higher priority process!
            return arrivals.at(x).arrivalTime - time; // return the amount of time before this process arrives.
            break;
        }
        x++;
    }
    // Did not find a Process with a higher priority.
    return currentProcess.remainingCPUBurst;
}
