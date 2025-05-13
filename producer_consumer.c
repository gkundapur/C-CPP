#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE 5
#define NITEMS   10

int buffer[BUF_SIZE];
int in = 0;
int out = 0;

sem_t empty;  // to count empty slots
sem_t full;     // to count filled slots
//pthread_mutex_t mutex; // mutex for mutual exclusion
sem_t mutex;

/**********************************************************
do {
    produce item
    wait(empty)
    wait(mutex)

    // place in buffer

    signal(mutex)
    signal(full)
} while(1);
**********************************************************/
void *
producer(void *arg)
{
    //for (int i = 0; i < NITEMS; i++) {
    do {
        int item = rand() % 100;
        sem_wait(&empty);
        //pthread_mutex_lock(&mutex);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("producer produced: %d at index: %d\n", item, in);
        in = (in + 1) % BUF_SIZE;

        //pthread_mutex_unlock(&mutex);
        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    } while (1);

    return NULL;
}

/*************Consumer**********************************
do {
    wait(full)
    wait(mutex)

    // consume item from buffer

    signal(mutex)
    signal(empty);
} while(1);
*******************************************************/
void *
consumer(void *arg)
{
    do {
        sem_wait(&full);
        //pthread_mutex_lock(&mutex);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("consumer consumed: %d at index: %d\n", item, out);
        out = (out + 1) % BUF_SIZE;
        //pthread_mutex_unlock(&mutex);
        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    } while(1);

    return 0;
}

int
main(void)
{
    pthread_t prod, cons;

    sem_init(&empty, 0, BUF_SIZE); // empty = 5
    sem_init(&full, 0, 0);  // full = 0
    sem_init(&mutex, 0, 1);
    //pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    //pthread_mutex_destroy(&mutex);
    sem_destroy(&mutex);

    return 0;
}
