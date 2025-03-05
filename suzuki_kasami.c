#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>
#include <pthread.h>

#define N 10

int request[N];
int token=0;
int turn=0;
int granted[N];

void *process(void *vargp)
{
	int id=*(int *)vargp;
	int i;
	srand(time(0));
	int wait=rand()%10+1;
	int critical=rand()%10+1;
	int x;
	for(i=0;i<wait;i++)
		sleep(1);
	printf("Process %d is requesting for resource\n",id);
	request[id]=1;
	turn=1-turn;
	x=turn;
	granted[id]=0;
	while(granted[id]==0)
	{
		if(token==0)
		{
			token=1;
			granted[id]=1;
		}
		else
		{
			if(request[1-x]==0)
				turn=1-turn;
			else
			{
				request[id]=0;
				while(granted[1-x]==1)
				{
					if(turn==x)
						request[id]=1;
				}
			}
		}
	}
	for(i=0;i<critical;i++)
		sleep(1);
	token=0;
	granted[id]=0;
	request[id]=0;
	printf("Process %d has released resource\n",id);
	return NULL;
}

int main()
{
	pthread_t tid[N];
	int i;
	int id[N];
	for(i=0;i<N;i++)
	{
		id[i]=i;
		pthread_create(&tid[i],NULL,process,&id[i]);
	}
	for(i=0;i<N;i++)
		pthread_join(tid[i],NULL);
	return 0;
}
