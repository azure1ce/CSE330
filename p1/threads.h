/*
Assignment: 1
Class: CSE330
Name: Jingming Tan
Date:07/17/2019
*/

#include <stdlib.h>
#include "q.h"

extern TCB_t *RunQ;

void start_thread(void (*function)(void))
{   
    // begin pseudo code
    void *stack;
    TCB_t *tcb;
    stack = malloc(8192);    //allocate a stack (via malloc) of a certain size (choose 8192)
    tcb = (TCB_t*)malloc(sizeof(TCB_t));    //allocate a TCB (via malloc)
    init_TCB(tcb, function, stack, 8192);   //call init_TCB with appropriate arguments
    AddQueue(&RunQ, tcb);  //call addQ to add this TCB into the “RunQ” which is a global header pointer   
    //end pseudo code
}

void run()
{
    // real code
    ucontext_t parent; // get a place to store the main context, for faking
    getcontext(&parent); // magic sauce
    swapcontext(&parent, &(RunQ->context)); // start the first thread
}
void yield() // similar to run
{
    TCB_t *tempPtr = RunQ;  
    RotateQ(&RunQ); //rotate the run Q;
    swapcontext(&(tempPtr->context),&(RunQ->context)); //swap the context, from previous thread to the thread pointed to by RunQ
}