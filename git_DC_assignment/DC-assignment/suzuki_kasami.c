#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

typedef enum messageType
{
    MESSAGE_INIT,
    MESSAGE_CS,
    MESSAGE_TOKEN
} messageType_t;

typedef struct message
{
	messageType_t msgType;
	int threadId;
	int value;
} Message_t;

pthread_t tid;
pthread_mutex_t cs_lock, release_lock, sendToken_lock, rn_lock, request_lock, token_lock, receive_lock;

// No token: 0, otherwise: 1
int hasToken = 0;
int numtasks;

// Not in CS: 0, otherwise: 1
int inCS = 0;

int reqForToken = 0;

int threadId;

int *RN, *LN, *TokenQ;
int front = -1, rear = -1;

void initializeLocks(void)
{
	if (pthread_mutex_init(&cs_lock, NULL) != 0)
		exit(0);

	if (pthread_mutex_init(&sendToken_lock, NULL) != 0)
		exit(0);

	if (pthread_mutex_init(&rn_lock, NULL) != 0)
		exit(0);

	if (pthread_mutex_init(&request_lock, NULL) != 0)
		exit(0);

	if (pthread_mutex_init(&token_lock, NULL) != 0)
		exit(0);

    if (pthread_mutex_init(&receive_lock, NULL) != 0)
        exit(0);

    if (pthread_mutex_init(&receive_lock, NULL) != 0)
        exit(0);
}
	
int
max(int a, int b)
{
	return a > b ? a : b;
}

nt
random_uniform(int l, int u)
{
    return rand() % (++u - l) + l;
}

char *gettime(char *buf)
{
    time_t timer;
    struct tm *tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(buf, 10, "%H:%M:%S", tm_info);
    return buf;
}

int isEmpty()
{
    if (front == -1)
        return 1;
    return 0;
}

// Add process id to tokenReqQ
void enQueue(int Q[], int numOfPids, int pid)
{

    if (front == -1)
        front = 0;
    rear = (rear + 1) % numOfPids;
    Q[rear] = pid;
    printf("\n Inserted P[%d]\n", pid);
}

// Remove process id from tokenReqQ
int deQueue(int Q[], int numOfPids)
{
    int thisPid;
    if (isEmpty())
    {
        printf("\n Queue is empty !! \n");
        return (-1);
    }
    else
    {
        thisPid = Q[front];

        // Q has only one element, so we reset the front and rear
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % numOfPids;
        }
        printf("\n Removed P[%d]\n", thisPid);
        return (thisPid);
    }
}

void
sendToken(int receiver)
{
	Message_t message;

	message.message = MESSAGE_TOKEN;
	message.thisPid = threadId;
	message.value = -1; //indicates token message

	printf("Sending token to = %d\n", receiver);
	fflush(stdout);
	MPI_Send(&message, sizeof(message), MPI_INT, receiver, tag, MPI_COMM_WORLD);
	sleep(2);
}

void *
receive_msg(void *arg)
{
	Message_t message;
	MPI_Status status;
    char time[32];

	MPI_Recv(&message, sizeof(message), MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    if (message.msgType == MESSAGE_INIT) {
		pthread_mutex_lock(&receive_lock);
        printf("%s: Recieved init message\n", gettime(time));
	    printf("message.msgType = %d, message.threadId = %d, message.value = %d\n",
			message.msgType, message.threadId, message.value);
        fflush(stdout);
        RN[message.threadId] = message.value;
        sleep(2);
	    pthread_mutex_unlock(&receive_lock);
    }

	if (message.msgType == MESSAGE_CS) {
        pthread_mutex_lock(&cs_lock);
        printf("%s: %d received request(%d, %d) from %d\n",
				gettime(time), threadId, message.threadId, message.value, message.threadId);
        fflush(stdout);
		RN[message.threadId] = max(RN[message.threadId], message.value);

			// Check for out of date requests
		if (RN[message.threadId] > message.value) {
			printf("%s: Request from %d is out of date\n", gettime(time), message.threadId);
			fflush(stdout);
		}

			// If process Sj has idle token and RN[i] = LN[i] + 1, then send token
		if (hasToken == 1 && inCS == 0 && (RN[message.threadId] == (LN[message.threadId] + 1))) {
			hasToken = 0;
			sendToken(message.threadId);
		}
		pthread_mutex_unlock(cs_lock);
    }

    if (message.msgType == MESSAGE_TOKEN) {
		pthread_mutex_lock(&token_lock);
		printf("%d receives a token(%d, %d)\n", threadId, message.value, message.threadId);
		fflush(stdout);
		hasToken = 1;
		reqForToken = 0;
		LN = message.threadId;
		
        //TODO
        //update LN
        //update tokenQue
        //enter CS on receiving token
        //enterCS()
    }

    pthread_mutex_unlock(&cs_lock);

	return NULL;
}

void exitCS(void)
{
    char time[32];

    pthread_mutex_lock(&release_lock);

    printf("%s: %d exits CS\n", gettime(time), threadId);

    LN[threadId] = RN[threadId];

    /**
     * For every site whose ID is not in tokenQue,
     * append it's siteID to tokenQue if RN[siteID] == LN[siteID] + 1
     */

    //TODO
    pthread_mutex_unlock(&release_lock);        
}

void enterCS(void)
{
    char time[32];

    pthread_mutex_lock(&cs_lock);
    if (hasToken == 1) {
        inCS = 1;

        printf("%s: %d received token and enters CS\n", gettime(time), threadId);
        fflush(stdout);
        sleep(2);
        printf("%s: %d finishes CS\n", gettime(time), threadId);
        fflush(stdout);
        inCS = 0;
        exitCS();
    }
    pthread_mutex_unlock(&cs_lock);
}

void 
request_Token(int numtasks)
{
	Message_t message;
	int i, tag = 0;
    char time[32];

	pthread_mutex_lock(&request_lock);

    if (hasToken == 0) {
        RN[threadId] += 1;

		message.msgType = MESSAGE_CS;
		message.threadId = threadId;
		message.value = RN[threadId];

        for (i = 0; i < numtasks; i++) {
            if (threadId != i) {
		        printf("%s: %d sends request(%d, %d) to %d\n", gettime(time), threadId, threadId, message.value, i);
                fflush(stdout);

		        MPI_Send(&message, sizeof(message), MPI_INT, i, tag, MPI_COMM_WORLD);
                sleep(2);
		    }
	    }
    }

	pthread_mutex_unlock(&request_lock);
}
	
	
int
main(int argc, char **argv)
{
	int error;
    char time[32];
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	//Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	// Get the threadId of the process
	//int threadId;
	MPI_Comm_rank(MPI_COMM_WORLD, &threadId);

	if (pthread_mutex_init(&request_lock, NULL) != 0) {
		printf("Failed to pthread_mutex_init\n");
		return 1;
	}

	if (pthread_mutex_init(&receive_lock, NULL) != 0) {
		return 1;
	}

	RN = (int *)malloc(numtasks * sizeof(int));
	if (RN == NULL) {
		printf("Error in allocating memory for RN\n");
		return 1;
	}
    memset(RN, 0, sizeof(RN));

	LN = (int *)malloc(numtasks * sizeof(int));
	if (LN == NULL) {
		printf("Error in allocating memory for LN\n");
		return 1;
	}
    memset(LN, 0, sizeof(LN));

	TokenQ = (int *)malloc(numtasks * sizeof(int));
	if (TokenQ == NULL) {
		printf("Error in allocating memory for TokenQ\n");
		return 1;
	}
	memset(TokenQ, 0, sizeof(TokenQ));

	error = pthread_create(&tid, NULL, receive_msg, NULL);
	if (error != 0) 
			printf("pthread_create error: %s\n", strerror(error));

	if (threadId == 0) {
        printf("%s: %d has a token initially\n", gettime(time), threadId);
        fflush(stdout);

		hasToken = 1;
        RN[threadId] = 1;

		// send Request array of 0 to all process
        for (int i = 0; i < numtasks; i++) {
            if (threadId != i) {
                Message_t message;

                message.msgType = MESSAGE_INIT;
                message.value = RN[threadId];
                message.threadId = threadId;

			    MPI_Send(&message, sizeof(message), MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        for (int i = 0; i < numtasks; i++) {
            printf("%s: Initial RN(%d) = [", gettime(time), i);
            fflush(stdout);
            for (int j = 0; j < numtasks; j++) {
                printf("%d", RN[j]);
                if (j != numtasks - 1)
                    printf(", ");
                fflush(stdout);
            }
            printf("]\n");
            fflush(stdout);
        }
	}

    while(1) {
	    if (hasToken == 0) {
            sleep(2);
		    request_Token(numtasks);
        } else if(inCS == 0) 
            enterCS();

        while (reqForToken)
            sleep(3);
    }


	//pthread_join(tid, NULL);

	MPI_Finalize();

	return 0;
}
