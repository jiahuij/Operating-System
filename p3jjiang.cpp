#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

using namespace std;

int pool [10];
static int in=0, out=0;

pthread_mutex_t mutex;
sem_t empty, full;


int insert_item(int in_item)
{
 
 if(in ==10)
	{
		return-1;
	}	
 else
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		pool[in]=in_item;
		in++;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		return 0;		
	}
	return -0;
}

int remove_item(int out_item)
{

 if(in == 0)
	{
		return-1;
	}	
 else
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		in--;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		return 0;		
	}
	return -0;
}

int nump = 1;
void *producer(void* param)
{

	int item;

	while(true)
	{
		srand(time(NULL));

		int sleepTime = rand()%6+0;
		sleep(sleepTime);

		item = rand()%20+0;

		if(insert_item(item))
			cout<<" P: pool is full"<<endl;
		else
			cout<<"producer "<<(unsigned int)pthread_self()<<" produced "<<item<<" in buffer "<< in-1 <<endl;

	pthread_exit(0);
	}
		

	return 0;
}
int numc = 1;
void *consumer(void* param)
{


	int item;

	while(true)
	{
		srand(time(NULL));

		int sleepTime = rand()%6+0;
		sleep(sleepTime);
		
		item = pool[in];

		if(remove_item(item))
			cout<<"C: pool is empty"<<endl;
		else
			cout<<"consumer "<<(unsigned int)pthread_self()<<" consumed "<<pool[in]<<" from buffer "<< in<<endl;


		pthread_exit(0);
		}
	return 0;

}

int main()
{

	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);
	int sleepTimeBeforeTerminate, numOfProdT,numOfConsT;

	cout<<"How long to sleep before terminating? ";
	cin>>sleepTimeBeforeTerminate;

	cout<<"How many producer threads? ";
	cin>>numOfProdT;

	cout<<"How many consumer threads ? ";
	cin>>numOfConsT;

	pthread_t *thread;
	thread = (pthread_t *) malloc(numOfProdT*sizeof(pthread_t));
	pthread_attr_t attr;
	pthread_attr_init(& attr);

	for(int i = 0; i < numOfProdT; i++)
	{
		pthread_create(&thread[i],&attr,producer,(void*)&i);

	}
	
	for(int i = 0; i < numOfProdT; i++)
	{
		 pthread_join(thread[i],NULL);
	}

	for(int i = 0; i < numOfConsT; i++)
	{
		pthread_create(&thread[i],&attr,consumer,(void*)&i);
	}
	
	for(int i = 0; i < numOfConsT; i++)
	{
		pthread_join(thread[i],NULL);
	}

	sleep(sleepTimeBeforeTerminate);
	
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
	

	pthread_exit(NULL);

return 0;
}
