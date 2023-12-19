
CPU Scheduler

This program is meant to run on Linux servers, this program was tested on the ODU Linux server.
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
            
Producer-Consumer

CS471 Project, Part 2
Bradley Hampton
12/3/2023

// Description --------------------------------------------------------------------------------------
This program demonstrates usage of counting semaphores in order to simulate a producer-consumer problem scenario. The program is invoked with the following parameters.
    Runtime     - The total amount of time in seconds the simulation will run for.
    Producers   - The total number of producers in the simulation.
    Consumers   - The total number of consumers in the simulation

This program was designed to be run on the ODU CS Linux server. Parameters are supplied to
the program through the command line.

// Build command ------------------------------------------------------------------------------------

With your working directory being CS471PROJECT, issue this command to build application:

g++ -pthread  PRODUCER-CONSUMER/ProducerConsumer.cpp -o PRODUCER-CONSUMER/ProducerConsumer

// Input/Output -------------------------------------------------------------------------------------

    In my implementation, I do not use input files to supply my program with its parameters.

    In order to produce output files for this project, we utilize shell scripts
        2sec.sh             4sec.sh             6sec.sh             to invoke the program and append output to
        2sec-output.txt     4sec-output.txt     6sec.output.txt     respectively.

    In order to produce the output files, invoke the shell scripts at the command line.

        i.e.
            PRODUCER-CONSUMER/2sec.sh
            PRODUCER-CONSUMER/4sec.sh
            PRODUCER-CONSUMER/6sec.sh
    
// Results Summary ----------------------------------------------------------------------------------

    Throughput is maximized by having an equal and large amount of producers and consumers. For example, across all
    timeframes, 2 sec, 4 sec, and 6 sec; 16 producers and 16 consumers produces the highest throughput.

    Additionally, we can see that in all cases, our throughput, on average, approximates the minimum between the number or producers and consumers present.

    For example, here's a snippet from my run of 6sec.sh:

        Sleep = 6, Producers = 4, Consumers = 4 	 Throughput:	2.666667	 min(Producers, Consumers) = 4 ~2.667
        Sleep = 6, Producers = 4, Consumers = 16 	 Throughput:	5.333333	 min(Producers, Consumers) = 4 ~5.333
        Sleep = 6, Producers = 16, Consumers = 1 	 Throughput:	1.500000	 min(Producers, Consumers) = 4 ~1.500

    That said, even if we have a set amount of Producers, having MORE Consumers can certainly help with throughput.

        Sleep = 6, Producers = 1, Consumers = 1 	 Throughput:	0.333333	 
        Sleep = 6, Producers = 1, Consumers = 4 	 Throughput:	1.000000	 
        Sleep = 6, Producers = 1, Consumers = 16 	 Throughput:	1.333333

    While not to a drastic extent, we still see that as we increase our number of consumers, our throughput increases!

    In my implementation, the rate of producers producing and consumers consuming is relatively consistently, except for some random noise.

    If the rate of producing and rate of consuming were different, then this would impact the "proper ratio" that creates this optimum throughput. That said, in any situation with producers and consumers, if our buffer is full, increasing the amount of consumers would help our throughput. When the buffer is constantly empty, more producers would increase throughput.




