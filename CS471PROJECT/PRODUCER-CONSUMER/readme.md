


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


