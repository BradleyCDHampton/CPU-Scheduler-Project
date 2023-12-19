#include <pthread.h>
#include <semaphore.h>

/* buffer.h */
typedef int buffer_item;
#define BUFFER_SIZE 5

class Buffer {
    private:
        int producerReadHead;
        int consumerReadHead;

    public:
        sem_t* empty;
        sem_t* full;
        pthread_mutex_t* mutex; // mutex lock

    Buffer() {
        buffer_item buffer[BUFFER_SIZE];
        sem_init(empty, 0, BUFFER_SIZE); // initialize semaphores, move?
        sem_init(full, 0, 0);
        pthread_mutex_init(mutex,NULL);

        producerReadHead = 0;
        consumerReadHead = 0;
    }
};



/*
The buffer will be manipulated with two functions, insert item() and
remove item(), which are called by the producer and consumer threads,
respectively. A skeleton outlining these functions appears in Figure 5.24.
The insert item() and remove item() functions will synchronize the
producer and consumer using the algorithms outlined in Figures 5.9 and
5.10. The buffer will also require an initialization function that initializes the
mutual-exclusion object mutex along with the empty and full semaphores.
The main() function will initialize the buffer and create the separate
producer and consumer threads. Once it has created the producer and
consumer threads, the main() function will sleep for a period of time and,
upon awakening, will terminate the application. The main() function will be
passed three parameters on the command line:

*/