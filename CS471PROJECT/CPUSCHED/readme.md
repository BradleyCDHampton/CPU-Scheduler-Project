
This program is meant to run on the ODU Linux servers.
In order to run this program on your machine, ensure that your working directory is CS471PROJECT

// INPUT/OUTPUT files ----------------------------------------------------------------------------------

Datafile1-txt.txt               - is the original data file included with the assignment.
Datafile2-txt.txt               - is a smaller example with 10 processes; used to verify by hand if the results are correct.
Datafile3-random_order-txt.txt  - tests whether or not the ordering of processes on an inputfile changes the results;
                                    should produce output identical to Datafile2-txt.txt
Datafile4-same_arrival_time     - tests whether the scheduler produces errors when multiple processes have the same arrival time.
Datafile5-tiebreakers-txt.txt    - considers cases where multiple processes share the same priority/CPU Burst Cycle/

cd [a file path to CS471PROJECT]
With your working directory configured properly, you can run this program with the following commands:

Build command:
g++ CPUSCHED/CPUSchedulerDriver.cpp -o CPUSCHED/CPUSchedulerDriver

Execute command:

The same source file is invoked to run all three scheduling algorithms. The algorithm during execution
is selected using command-line arguments. If no argument is specified, the process is aborted.

./CPUSCHED/CPUschedulerDriver [filepath] [mode]
    [filepath] - a filepath to the inputFile that we are using for this run of the program.
    [mode] - the mode in which we will invoke the scheduler; legal options are FCFS, SJF, PRIORITY
        FCFS - first-come first-serve scheduling.
        SJF - shortest job first w/o preemption.
        PRIORITY - priority scheduling with preemption.

Examples of program execution (copy and paste these into the command line):
    ./CPUSCHED/CPUSchedulerDriver CPUSCHED/Datafile1-txt.txt FCFS
    ./CPUSCHED/CPUSchedulerDriver CPUSCHED/Datafile1-txt.txt SJF
    ./CPUSCHED/CPUSchedulerDriver CPUSCHED/Datafile1-txt.txt PRIORITY

Output files are created within the CPUSCHED directory, they are tited by appending "[scheduling algorithm]-output"
to the original file's title.
    
    i.e. Data1-txt.txt w/ SJF > Data1-txt-SJF-output.txt

Each execution's output is also mirrored to the terminal.

// RESULTS SUMMARY AND EXPLANATION ------------------------------------------------------------------------------

    The following is a discussion related to the statistics output by each algorithm, relating to the output
    from Datafile1-txt.txt.

        [Number of processes]:
            Consistent between runs, given that the algoritms do not change our input.

            Calculated through counting the number of processes in our input file. Every process is stored in a table called arrivals, and processes is set to equal the size of this array.

        [Total elapsed time]:
            Interestingly, this is also consistent between runs. Due to there being no "overhead" cost of swapping in and out processes, no additional time will elapse during the SJF and PRIORITY algorithms. If we had assigned an overhead cost for these methods in this simulation, then we could expect for there to be some additional elapsed time in the SJF and PRIORITY algorithms; however, this would likely be miniscule.

             Calculated using a "time" variable defined in CPUScheduler class definition. This segregates the overall execution time of this program from what the time should look like for our simulation.

        [Throughput]:
            number of processes / elapsed time

            Given that both processes and elapsed time are consistent between algorithms, this is also consistent between algorithms.

        [CPU Utilization]:
            total burst time / elapsed time

            The sum total of all burst time is given via the input file; elapsed time is consistent between algorithms.
            CPU Utilization does not change between algorithms.

        [Average waiting time]:
            sumWaitingTime/(processCount + preemptionCount)

            SJF has the shortest turnaround time.       14.0838 CPU Burst cycles
            FCFS                                        17.6511 CPU Burst cycles
            PRIORITY                                    21.4542 CPU Burst cycles

            The SJF algorithm can cause starvation when processes with exceptionally long burst times enter the picture.
            This can lead to multiple processes with a long burst time waiting while SJF executes shorter jobs.

            FCFS and PRIORITY have no significant advantages against one another in this metric. They may perform better or worse than one another in different situations depending on which processes have a higher priority.
                
        [Average turnaround time]:
            sumTurnaround/processCount

            where sumTurnaround is defined as a running total. When a process exits, we add the time between it exiting and it arriving at the ready state to sumTurnaround.

            SJF has the shortest turnaround time.       35.3158 CPU Burst cycles
            FCFS                                        38.883 CPU Burst cycles
            PRIORITY                                    42.6862 CPU Burst cycles

            PRIORITY is most likely disadvantaged because it may suffer from starvation of processes with lower priority.
            SJF has an excellent turnaround time because processes that will finish very quickly will be instantly prioritized, so in these cases their turnaround time equals their CPU burst time.

        [Average response time]
            sumResponse/processCount

            Where sumResponse time is calculated as a running total of the time has passed since the first moment a process
            has exited the running state (either by being preempted and going back to the ready queue or by exiting after it exits after finishing)

            PRIORITY                                    29.4172 CPU Burst cycles
            SJF                                         35.3158 CPU Burst cycles
                                                        The same as its turnaround time, given we have implemented
                                                        non-preemptive SJF.
            FCFS                                        38.883 CPU Burst cycles
                                                        The same as its response time, since FCFS is non-preemptive.
            





    Statistics for the Run:
  Number of processes: 10
  Total elapsed time: 10264 CPU Burst cycles
  Thoroughput: 0.000974279 processes/CPU Burst cycle
  CPU utilization: 99.9026%
  Average waiting time: 8930.6 CPU Burst cycles
  Average turnaround time: 9956 CPU Burst cycles
  Average response time: 8930.6 CPU Burst cycles


