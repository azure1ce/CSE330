/*
Assignment: 1
Class: CSE330
Name: Jingming Tan
Date:07/17/2019
*/

#include <string.h>
#include <unistd.h>
#include <ucontext.h>

typedef struct TCB_t
{
    int number;
    struct TCB_t *nextPtr;
    struct TCB_t *prevPtr;
    ucontext_t context;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));			 // wash, rinse
    getcontext(&tcb->context);				 // have to get parent context else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);		 //context is now cooked
}