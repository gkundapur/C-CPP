#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// Has No Token: 0, Has Token: 1
int hasToken = 0;

// Process not in CS: 0, In CS : 1
int inCS = 0;
int waitingForToken = 0;
// No. of processes
int numProcesses;
int front = -1, rear = -1;


typedef enum messageType
{
    INITMSG,
    REQCSMSG,
    TOKENMSG
} messageType_t;

typedef struct message
{
    messageType_t msgType;
    int threadId;
    int sn;
} Message_t;

pthread_t tid;
pthread_mutex_t cs_lock, token_lock, rn_lock, ln_lock, release_lock, request_lock, send_lock,receive_lock;

int reqForToken = 0;
int threadId;
// RN Array and LN Array
int *RN;
int  *LN; 
int *TokenReqQ;

int initializeLocks(); 
void destroylocks();
void request_token(int);
void send_token(int, int);
void enter_CS();
void release_CS();
void *init_receive_msg(void *arg);
void receive_msg();
int search_ReqQ(int Q[], int, int);
int isFull();
int isEmpty();
void enQueue(int Q[], int, int);
int deQueue(int Q[], int);
int max(int , int );

int
random_uniform(int l, int u)
{
    return rand() % (++u - l) + l;
}

int main(int argc, char **argv)
{
    // Initialize the environment
    int pcreatestatus;
    int lockstatus;
    int numIterations = 25;
    int thisIteration = 0;
    int i,j;
    Message_t new_message;
    

    // Initialize locks required
    lockstatus = initializeLocks();
    if (lockstatus == 1)
        return 1;

    // MPI Environment initialization
    MPI_Init(NULL, NULL);
    // Get number of processes in play
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    // Get the thread id of the main process
    MPI_Comm_rank(MPI_COMM_WORLD, &threadId);

    RN = (int *)malloc(numProcesses * sizeof(int));
    LN = (int *)malloc(numProcesses * sizeof(int));
    TokenReqQ = (int *)malloc(numProcesses * sizeof(int));
    if (RN == NULL || LN == NULL || TokenReqQ == NULL)
    {
        printf("Error in allocating memory for RN or LN or TokenReqQ  \n");
        return 1;
    }
    // Initialize the RN, LN with 0
       
    for (j=0;j < numProcesses;j++){
        RN[j] = 0;
        LN[j] = 0;
    }
     
   // Create the main thread
    pcreatestatus = pthread_create(&tid, NULL, init_receive_msg, NULL);

    if (pcreatestatus != 0)
    {
        printf("pthread_create error !!");
        return 1;
    }

   

    if (threadId == 0)
    {
        printf("Process P[%d] has a token initially\n", threadId);
        fflush(stdout);
        
        hasToken = 1;
        RN[threadId] = 0;
        
       }

        while (1)
        {
            
            if (hasToken == 0)
            {
                sleep(random_uniform(1, 3));
                request_token(numProcesses);
                receive_msg();
            }
            else if (inCS == 0)
                enter_CS();
            while (waitingForToken)
                sleep(random_uniform(1, 3));
            

        }


    
   destroylocks();
  
   pthread_join(tid, NULL);
   MPI_Finalize();
   return 0;
}

int initializeLocks()
{
    if (pthread_mutex_init(&cs_lock, NULL) != 0)
    {
        printf("Lock initialization failed for cs_lock");
        return 1;
    }

    if (pthread_mutex_init(&rn_lock, NULL) != 0)
    {
        printf("Lock initialization failed for rn_lock");
        return 1;
    }

    if (pthread_mutex_init(&request_lock, NULL) != 0)
    {
        printf("Lock initialization failed for request_lock"); 
        return 1;
    }

    if (pthread_mutex_init(&token_lock, NULL) != 0)
    {
        printf("Lock initialization failed for token_lock");
        return 1;
    }

    if (pthread_mutex_init(&receive_lock, NULL) != 0)
    {
        printf("Lock initialization failed for receive_lock");
        return 1;
    }

    

    if (pthread_mutex_init(&release_lock, NULL) != 0)
    {
        printf("Lock initialization failed for release_lock"); 
        return 1;
    }

    if (pthread_mutex_init(&send_lock, NULL) != 0)
    {
        printf("Lock initialization failed for send_lock"); 
        return 1;
    }

    if (pthread_mutex_init(&ln_lock, NULL) != 0)
    {
        printf("Lock initialization failed for ln_lock"); 
        return 1;
    }
}

void destroylocks()
{
    pthread_mutex_destroy(&cs_lock);
    pthread_mutex_destroy(&rn_lock);
    pthread_mutex_destroy(&request_lock);
    pthread_mutex_destroy(&token_lock);
    pthread_mutex_destroy(&release_lock);
    pthread_mutex_destroy(&send_lock);
    pthread_mutex_destroy(&receive_lock);
    pthread_mutex_destroy(&ln_lock);
}

void request_token(int numProcesses)
{
    
    Message_t req_message;
    int i, tag = 0;
    pthread_mutex_lock(&request_lock);
    //printf("\nMy Thread id : %d, Hastoken : %d\n",threadId,hasToken);
   

    if (hasToken == 0 )
    {
        RN[threadId] += 1;

        req_message.msgType = REQCSMSG ;
        req_message.threadId = threadId;
        req_message.sn = RN[threadId];

        for (i = 0; i < numProcesses; i++)
        {
            if (threadId != i)
            {
                printf("Process P[%d] sending Request(%d, %d) to Process P[%d]\n", threadId, threadId, req_message.sn, i);
                fflush(stdout);

                MPI_Send(&req_message, sizeof(req_message), MPI_INT, i, tag, MPI_COMM_WORLD);
                
                sleep(2);
            }
        }

        
    }
    
    pthread_mutex_unlock(&request_lock);
}

void enter_CS()
{

    pthread_mutex_lock(&cs_lock);

    if (hasToken == 1)
    {
        inCS = 1;

        printf("\nProcess P[%d] has received token and is entering critical section \n", threadId);
        fflush(stdout);
        sleep(random_uniform(3, 7));
        printf("\nProcess P[%d] has finished  critical section \n", threadId);
        fflush(stdout);
        inCS = 0;
        
        //hasToken = 0;
        release_CS();
        fflush(stdout);
    }
    pthread_mutex_unlock(&cs_lock);
}

/*void send_token(int srcProcessId, int destProcessId){
    // printf ("TOKENMSG");
     pthread_mutex_lock(&send_lock);
     Message_t token_message;
     int tag = 1;
     printf("Into send Token");
     fflush(stdout);
     
     token_message.msgType = TOKENMSG;
     token_message.sn = 0; // Indicating this is a token message
     token_message.threadId = srcProcessId;
     MPI_Send(&token_message, sizeof(token_message), MPI_INT, destProcessId, tag, MPI_COMM_WORLD);
     pthread_mutex_unlock(&send_lock);

}*/

void release_CS()
{

    pthread_mutex_lock(&release_lock);

    int nextProcessID;

    printf("Process P[%d] is exiting critical section \n", threadId);
    fflush(stdout);

    //pthread_mutex_lock(&ln_lock);
    LN[threadId] = RN[threadId];
    //pthread_mutex_unlock(&ln_lock);

    //printf("LN[0] : %d, RN[0] : %d\n",LN[0],RN[0]);
    
    //Add request received from other processes for token to  Token request queue
    for (int i = 0; i < numProcesses; i++)
    {
         printf("\nRN[%d] : %d, LN[%d]: %d ",i,RN[i],i,LN[i]);
         fflush(stdout);
        if (threadId != i)
        {

                if (RN[i] == LN[i] + 1)
                {
                    //printf("Into enqueue process to add to token q\n");
                    enQueue(TokenReqQ, numProcesses, i);
                }
            
        }
    }
    // If Token Request Queue is not empty send the token to the process in the head of queue.
    if (isEmpty() != 1)
    {

        printf("Contents of Token Request Queue \n [");
       
        if (front == rear && front == 0)
            printf("%d ]\n", TokenReqQ[front]);
        else {
        for (int i = front; i != rear; i = (i + 1) % numProcesses)
        {
            printf("%d ", TokenReqQ[i]);
            if (i != rear)
                printf(",");
        }
        printf("]\n");
        }
        hasToken = 0;
        nextProcessID = deQueue(TokenReqQ, numProcesses);
        printf("Process P[%d] is sending token to Process P[%d]\n", threadId, nextProcessID);
        fflush(stdout);
        //send_token(threadId,nextProcessID);

        Message_t token_message;
        token_message.msgType = TOKENMSG;
        token_message.sn = 0; // Indicating this is a token message
        token_message.threadId = threadId;
        MPI_Send(&token_message, sizeof(token_message), MPI_INT, nextProcessID, 1, MPI_COMM_WORLD);
        //sleep(2);
    }

    pthread_mutex_unlock(&release_lock);
}

void *init_receive_msg(void *arg)
{
	Message_t message;
	MPI_Status status;
    int i = 0;
   
    
	MPI_Recv(&message, sizeof(message), MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    printf("message.msgType = %d, message.threadId = %d, message.sn = %d\n", message.msgType, message.threadId, message.sn);
    
    pthread_mutex_lock(&receive_lock);

	if (message.msgType == REQCSMSG) {
        //pthread_mutex_lock(&rn_lock);
        printf("P[%d] received Request(%d, %d) from P[%d]\n",threadId, message.threadId, message.sn, message.threadId);
        fflush(stdout);

        //pthread_mutex_lock(&rn_lock);
		RN[message.threadId] = max(RN[message.threadId], message.sn);
        //pthread_mutex_unlock(&rn_lock);

       
        fflush(stdout);
		// Check for outdated requests
		if (RN[message.threadId] > message.sn) {
			printf("Request from P[%d] is expired \n", message.threadId);
			fflush(stdout);
		}

 
		// If process P has idle token and RN[i] = LN[i] + 1, then send token
        
		if (hasToken == 1 && inCS == 0 && (RN[message.threadId] == (LN[message.threadId] + 1))) {
			hasToken = 0;
			//send_token(threadId,message.threadId);
            Message_t token_message;
            token_message.msgType = TOKENMSG;
            token_message.sn = 0; // Indicating this is a token message
            token_message.threadId = threadId;
            MPI_Send(&token_message, sizeof(token_message), MPI_INT, message.threadId, 1, MPI_COMM_WORLD);
		}
        //printf ("RN %d",RN[message.threadId]);

       // pthread_mutex_unlock(&rn_lock);
    }
    

    if (message.msgType == TOKENMSG) {
       // pthread_mutex_lock(&token_lock);
        printf("Process P[%d] has received token\n",threadId);
        fflush(stdout);
        waitingForToken = 0;
        hasToken = 1;
        //enter CS on receiving token
        enter_CS();
        //pthread_mutex_unlock(&token_lock);
    }

	pthread_mutex_unlock(&receive_lock);

	return NULL;
}

void receive_msg()
{
	Message_t new_message;
	MPI_Status status;
    int i = 0;
   
    
	MPI_Recv(&new_message, sizeof(new_message), MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    printf("new message.msgType = %d, message.threadId = %d, message.sn = %d\n",
        new_message.msgType, new_message.threadId, new_message.sn);
    fflush(stdout);
    
    
	//printf("Into receive message : %d\n",i++);
   
    /*if (message.msgType == INITMSG) {
        printf(" P[%d] Recieved init message\n",message.threadId);
	    printf("message.msgType = %d, message.threadId = %d, message.sn = %d\n",
			message.msgType, message.threadId, message.sn);
        fflush(stdout);
        RN[message.threadId] = message.sn;
        sleep(2);
    }*/

    pthread_mutex_lock(&receive_lock);
	if (new_message.msgType == REQCSMSG) {
        
        printf("P[%d] received Request(%d, %d) from P[%d]\n",threadId, new_message.threadId, new_message.sn, new_message.threadId);
        fflush(stdout);

        pthread_mutex_lock(&rn_lock);
		RN[new_message.threadId] = max(RN[new_message.threadId], new_message.sn);
        pthread_mutex_unlock(&rn_lock);

		// Check for outdated requests
		if (RN[new_message.threadId] > new_message.sn) {
			printf("Request from P[%d] is expired \n", new_message.threadId);
			fflush(stdout);
		}

 
		// If process P has idle token and RN[i] = LN[i] + 1, then send token
        
		if (hasToken == 1 && inCS == 0 && (RN[new_message.threadId] == (LN[new_message.threadId] + 1))) {
			hasToken = 0;
			//send_token(threadId,message.threadId);
            Message_t token_message;
            token_message.msgType = TOKENMSG;
            token_message.sn = 0; // Indicating this is a token message
            token_message.threadId = threadId;
            printf("%d is sending token message\n", threadId);
            MPI_Send(&token_message, sizeof(token_message), MPI_INT, new_message.threadId, 1, MPI_COMM_WORLD);
            sleep(2);
		}
       

       
    }
    

    if (new_message.msgType == TOKENMSG) {
       // pthread_mutex_lock(&token_lock);
        //printf("Process P[%d] has received token",threadId);
        fflush(stdout);
        waitingForToken = 0;
        hasToken = 1;
        
        //enter CS on receiving token
        enter_CS();
        //pthread_mutex_unlock(&token_lock);
        
    }

	pthread_mutex_unlock(&receive_lock);
}

// Check if the queue is empty
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

int max(int x, int y)
{
	return x > y ? x : y;
}

