/*
Jingming Tan
CSE330-Operation Systems-2019-Summer
*/
#include <stdlib.h>
#include "q.h"

void start_thread(void (*function)(void))
{

    int stack_size = 8192;
    void * stackP = malloc(stack_size);

    TCB_t * tcb = NewItem();

    init_TCB(tcb, function, stackP, stack_size);

    AddQueue(runQ, tcb);
}

void run()
{
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &runQ->head->context);
}

void yield()
{
    ucontext_t current_context;
    getcontext(&current_context);
    runQ->head->context = current_context;
    RotateQ(runQ);
    ucontext_t new_context = runQ->head->context;
    swapcontext(&current_context, &new_context); 
}