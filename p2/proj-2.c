/*
Assignment: 2
Class: CSE330
Name: Jingming Tan
Date:08/01/2019
*/

#include "sem.h"

#define MAXBUFFER 10

void producer1();           // setup producer 1
void producer2();           // setup producer 2
void consumer1();           // setup consumer 1
void consumer2();           // setup consumer 1
void initBuffer();          // creat a buffer
void printBuffer();         // print out the result
void runMethodTwo();        // implement method 2
void infiniteLoop1();       // first function for the first method
void infiniteLoop2();       // second function for the first method

int globalVariable1 = 0;
int produce;
int consume;
int buffer[MAXBUFFER];
Semaphore *semaphoreOne;
Semaphore *emptyCount;
Semaphore *fillCount;
TCB_t *RunQ;

void infiniteLoop1()
{
	int index = 0;
	
	while(1)
	{
		P(semaphoreOne);
		index++;
		globalVariable1++;
		printf("\nThread 1\n");
		printf("Adds 1\n");
		printf("Local Index 1 = %d\n", index);
		printf("Global Index = %d\n", globalVariable1);
		sleep(1);
		V(semaphoreOne);
	}
}

void infiniteLoop2()
{
	int index = 0;
	
	while(1)
	{
		P(semaphoreOne);
		index += 4;
		globalVariable1 += 4;void runMethodOne()
{
	semaphoreOne = (Semaphore*)malloc(sizeof(Semaphore));
	InitSem(semaphoreOne, 1);
	InitQueue(&RunQ);
	start_thread(infiniteLoop1);
	start_thread(infiniteLoop2);
	printf("\nMethod 1\n");
	printf("\nStarting Global Index = %d\n", globalVariable1);
	printf("Starting Local Index 1 = 0\n");
	printf("Starting Local Index 2 = 0\n");
	sleep(1);
	run();
}

		printf("\nThread 2\n");
		printf("Adds 4\n");
		printf("Local Index 2 = %d\n", index);
		printf("Global Index = %d\n", globalVariable1);
		sleep(1);
		V(semaphoreOne);
	}
}

void runMethodTwo()
{
	produce = 0;
	consume = 0;
	emptyCount = (Semaphore*)malloc(sizeof(Semaphore));
	fillCount = (Semaphore*)malloc(sizeof(Semaphore));
	InitSem(emptyCount, 2);
	InitSem(fillCount, 0);
	InitQueue(&RunQ);
	initBuffer();
	start_thread(producer1);
	start_thread(producer2);
	start_thread(consumer1);
	start_thread(consumer2);
	printf("\nMethod 2\n");
	run();
}

void producer1()
{
	while(1)
	{
		P(emptyCount);
		
		buffer[produce] = 1;
		printf("Producer 1: ");
		printBuffer();
		
		if(produce < MAXBUFFER -1)
		{
			produce++;			
		}
		else
		{
			produce = 0;
		}
		
		sleep(1);
		V(fillCount);
		
	}
}

void producer2()
{
	while(1)
	{
		P(emptyCount);
		
		buffer[produce] = 1;
		printf("Producer 2: ");
		printBuffer();
		
		if(produce < MAXBUFFER -1)
		{
			produce++;			
		}
		else
		{
			produce = 0;
		}
		
		sleep(1);
		V(fillCount);
		
	}
}

void consumer1()
{
	while(1)
	{
		P(fillCount);
		
		buffer[consume] = 0;
		printf("Consumer 1: ");
		printBuffer();
		
		if(consume < MAXBUFFER - 1)
		{
			consume++;				
		}
		else
		{
			consume = 0;
		}
		
		sleep(1);
		V(emptyCount);
	}
}

void consumer2()
{
	while(1)
	{
		P(fillCount);
		
		buffer[consume] = 0;
		printf("Consumer 2: ");
		printBuffer();
		
		if(consume < MAXBUFF	emptyCount = (Semaphore*)malloc(sizeof(Semaphore));
	fillCount = (Semaphore*)malloc(sizeof(Semaphore));
	InitSem(emptyCount, 2);
	InitSem(fillCount, 0);
	InitQueue(&RunQ);
	initBuffer();
	start_thread(producer1);
	start_thread(producer2);
	start_thread(consumer1);
	start_thread(consumer2);
	printf("\nMethod 2\n");
	run();ER - 1)
		{
			consume++;				
		}
		else
		{
			consume = 0;
		}
		
		sleep(1);
		V(emptyCount);
	}
}

void initBuffer()
{
	int index;
	for(index = 0; index < MAXBUFFER; index++)
	{
		buffer[index] = 0;
	}
}

void printBuffer()
{
	int index;
	for(index = 0; index < MAXBUFFER; index++)
	{
		printf("%d", buffer[index]);
	}
	printf("\n");
}

int main()
{
	runMethodTwo();
	return 0;
}