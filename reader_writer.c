#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NREADERS 5
#define NWRITERS 2

sem_t rlock, wlock;
int readcount = 0;
int shared_data = 0;

void *
reader(void *arg)
{
	int id = *(int *)arg;

	while (1) {
		sem_wait(&rlock);  // obtain read lock
		readcount++;
		if (readcount == 1)
			sem_wait(&wlock); // if one reader, obtain wr lock

		sem_post(&rlock); // release read lock;

		printf ("Read %d is reading data: %d\n", id, shared_data);

		sem_wait(&rlock);
		readcount--;
		if (readcount == 0)
			sem_post(&wlock);

		sem_post(&rlock);
		sleep(1);
	}
	return NULL;
}

void *
writer(void *arg)
{
	int id = *(int *)arg;

	while (1) {
		sem_wait(&wlock);

		shared_data++;
		printf("Writer %d is writing data: %d\n", id, shared_data);

		sem_post(&wlock);

		sleep(2);
	}

	return NULL;
}
int
main(void)
{
	pthread_t readers[NREADERS];
	pthread_t writers[NWRITERS];

	sem_init(&rlock, 0, 1);
	sem_init(&wlock, 0, 1);

	int i;
	for (i = 0; i < NREADERS; i++) {
		int *id = (int *)malloc(sizeof(int));
		*id = i;
		pthread_create(&readers[i], NULL, reader, id);
	}

	for (i = 0; i < NWRITERS; i++) {
		int *id = (int *)malloc(sizeof(int));
		*id = i;
		pthread_create(&writers[i], NULL, writer, id);
	}

	for (i = 0; i < NREADERS; i++)
		pthread_join(readers[i], NULL);

	for (i = 0; i < NWRITERS; i++)
		pthread_join(writers[i], NULL);

	sem_destroy(&rlock);
	sem_destroy(&wlock);

	return 0;
}

