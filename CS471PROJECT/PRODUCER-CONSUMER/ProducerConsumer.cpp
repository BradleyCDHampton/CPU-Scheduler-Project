
// Bradley Hampton CS471 12/3/2023
// From Description "Operating Systems" 9th Edition

/*For this project, you will use standard counting semaphores for
empty and full and a mutex lock, rather than a binary semaphore, to represent
mutex. The producer and consumer—running as separate threads—will move
items to and from a buffer that is synchronized with the empty, full, and mutex
structures. You can solve this problem using either Pthreads or the Windows
API.*/

/*
Pthreads Thread Creation and Synchronization
Creating threads using the Pthreads API is discussed in Section 4.4.1. Coverage
of mutex locks and semaphores using Pthreads is provided in Section 5.9.4.
Refer to those sections for specific instructions on Pthreads thread creation and
synchronization.
*/

/*
The Producer and Consumer Threads
The producer thread will alternate between sleeping for a random period of
time and inserting a random integer into the buffer. Random numbers will
be produced using the rand() function, which produces random integers
between 0 and RAND MAX. The consumer will also sleep for a random period
of time and, upon awakening, will attempt to remove an item from the buffer.
An outline of the producer and consumer threads appears in Figure 5.26.
As noted earlier, you can solve this problem using either Pthreads or the
Windows API. In the following sections, we supply more information on each
of these choices.
*/

#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

// Shared Data Between Producer & Consumer --------------------------------------------------

buffer_item buffer[BUFFER_SIZE];
sem_t empty;                // counting semaphore
sem_t full;                 // counting semaphore
pthread_mutex_t mutex;      // mutex lock
int processesComplete = 0;

// Function Declarations --------------------------------------------------------------------

int remove_item(buffer_item *item);
int insert_item(buffer_item item);
void *producer(void *param);
void *consumer(void *param);

// Function Definitions ---------------------------------------------------------------------

void *producer(void *param){
    buffer_item item;
    while (true) {
        /* sleep for a random period of time */
        sleep(rand()%4);
        /* generate a random number */
    item = rand();
    if (insert_item(item))
        printf("report error condition");                      
    //else
        //printf("producer produced %d\n",item);
          
    }
}

void *consumer(void *param) {
    buffer_item item;
    while (true) {
        /* sleep for a random period of time */
        sleep(rand()%4);    //todo look into whether this was ... for a reason
    if (remove_item(&item))
        printf("report error condition");                      
    //else
        //printf("consumer consumed %d\n",item);
    }
}

// Attempts to insert an item into the buffer_list.
// Waits until it is able to do so.
int insert_item(buffer_item item) {

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    // critical section

    static int writeHead = 0;    //static variable; initialized only once.

    buffer[writeHead] = item;
    writeHead = (writeHead + 1) % BUFFER_SIZE;
    processesComplete++;
    // end critical section

    sem_post(&full);
    pthread_mutex_unlock(&mutex);

    return 0;
}


int remove_item(buffer_item *item) {

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    

    static int readHead = 0;    //static variable; initialized only once.
                                // will keep the same value thru different runs of this function.
    //critical section

    *item = buffer[readHead];
    readHead = (readHead + 1) % BUFFER_SIZE;
    processesComplete++;
    sem_post(&empty);
    pthread_mutex_unlock(&mutex);

    return 0;
}

int main(int argc, char *argv[]) {

/* 1. Get command line arguments argv[1],argv[2],argv[3] */

    int runTime = atoi(argv[1]);                 // How long to sleep before terminating.
    int totalProducerThreads = atoi(argv[2]);    // The number of producer threads.
    int totalConsumerThreads = atoi(argv[3]);    // The number of consumer threads.

/* 2. Initialize buffer */
    sem_init(&empty, 0, BUFFER_SIZE); // initialize semaphores, move?
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex,NULL);

/* 3. Create producer thread(s) */
    for (int i = 0; i < totalProducerThreads; i++){
        pthread_t thread;
        int status = pthread_create(&thread, NULL, producer, NULL); // include check to see if thread is successfully created? contine
    }

/* 4. Create consumer thread(s) */
    for (int i = 0; i < totalConsumerThreads; i++){
        pthread_t thread;
        int status = pthread_create(&thread, NULL, consumer, NULL); // include check to see if thread is successfully created? contine
    }

/* 5. Sleep */
    sleep(runTime);
/* 6. Exit */
    printf("Sleep = %d, Producers = %d, Consumers = %d \t Throughput:\t%f\t \n",
        runTime, totalProducerThreads, totalConsumerThreads, double(processesComplete)/runTime);
    exit(0); // exit and have all threads exit.
}