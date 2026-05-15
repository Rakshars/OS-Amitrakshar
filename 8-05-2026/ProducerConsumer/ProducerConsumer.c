#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8

/* Shared Buffer */
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

/* Number of items to produce */
int totalItems;

/* Semaphores */
sem_t empty;
sem_t full;

/* Mutex */
pthread_mutex_t mutex;

/* Produce Item */
int produceItem(int item)
{
    return item;
}

/* Consume Item */
void consumeItem(int item)
{
    printf("Consumed Item: %d\n", item);
}

/* Producer Thread */
void* producer(void* arg)
{
    int item;

    for (int i = 1; i <= totalItems; i++)
    {
        item = produceItem(i);

        /* Wait for empty slot */
        sem_wait(&empty);

        /* Enter critical section */
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Producer produced %d at position %d\n", item, in);

        in = (in + 1) % BUFFER_SIZE;

        /* Exit critical section */
        pthread_mutex_unlock(&mutex);

        /* Increase full count */
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

/* Consumer Thread */
void* consumer(void* arg)
{
    int item;

    for (int i = 1; i <= totalItems; i++)
    {
        /* Wait for filled slot */
        sem_wait(&full);

        /* Enter critical section */
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed %d from position %d\n", item, out);

        out = (out + 1) % BUFFER_SIZE;

        /* Exit critical section */
        pthread_mutex_unlock(&mutex);

        /* Increase empty count */
        sem_post(&empty);

        consumeItem(item);

        sleep(1);
    }

    pthread_exit(NULL);
}

/* Initialize Semaphores and Mutex */
void initialize()
{
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);
}

/* Destroy Resources */
void destroy()
{
    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);
}

/* Main Function */
int main()
{
    pthread_t producerThread;
    pthread_t consumerThread;

    printf("Enter number of items to produce: ");
    scanf("%d", &totalItems);

    /* Initialize */
    initialize();

    /* Create Threads */
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    /* Wait for Threads to Finish */
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    /* Cleanup */
    destroy();

    printf("\nProducer-Consumer Execution Completed\n");

    return 0;
}
