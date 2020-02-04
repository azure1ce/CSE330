/*
Assignment: 2
Class: CSE330
Name: Jingming Tan
Date:08/01/2019
*/

#include <unistd.h>
#include "threads.h"

// Semaphore data structure: A value field and a queue of TCBs.
typedef struct
{
	int value;
	struct TCB_t *semaQueue;
} Semaphore;

// Initializes the value field with the specified value.
void InitSem(Semaphore *initializeValue, int value)
{
	InitQueue(&initializeValue->semaQueue); // initializes the semaphore queue
	initializeValue->value = value;		// sets a number to value
}

// The P routine decrements the semaphore, and if the value is less than zero then blocks the process in the queue associated with the semaphore.
void P(Semaphore *P)
{
	P->value--; // decrement the semaphore 
	
	if(P->value < 0) // when value is less than zero
	{
		TCB_t *tempQueue;
		tempQueue = DelQueue(&RunQ);
		AddQueue(&P->semaQueue, tempQueue);
		swapcontext(&(P->semaQueue->context),&(RunQ->context));
	}
}

// The V routine increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queu
void V(Semaphore *V)
{
	V->value++; // increment the semaphore
	if(V->value <= 0) // when value is less than zero
	{
		TCB_t *tempQueue;
		tempQueue = DelQueue(&V->semaQueue);
		AddQueue(&RunQ, tempQueue);
	}
	yield();
}