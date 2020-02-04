/*
Jingming Tan
CSE330-Operation Systems-2019-Summer
*/
#include <stdlib.h>
#include "TCB.h"

#define ALLOC(t) (t*) calloc(1, sizeof(t))

typedef struct Queue
{
    struct TCB_t * head;
} Queue;

Queue * runQ;

TCB_t * NewItem();
Queue * InitQueue();
void AddQueue(struct Queue * queue, struct TCB_t * tcb);
TCB_t * DelQueue(struct Queue * queue);
void RotateQ(struct Queue * queue);
void FreeQueue(struct Queue * queue);

struct TCB_t * NewItem()
{
    TCB_t * element = ALLOC(struct TCB_t);
    element->prev = NULL;
    element->next = NULL;
    return element;
}

struct Queue * InitQueue()
{
    return ALLOC(struct Queue);
}

void AddQueue(struct Queue * queue, struct TCB_t * element)
{
    if(queue->head == NULL)
    {
        queue->head = element;
        queue->head->prev = queue->head;
        queue->head->next = queue->head;
    }
    else
    {
        TCB_t * tail = queue->head->prev;
        tail->next = element;
        element->prev = tail;
        tail = tail->next;

        tail->next = queue->head;
        queue->head->prev = tail;
    }
}

struct TCB_t * DelQueue(struct Queue * queue)
{
    if(queue->head == NULL)
    {
        return NULL;
    }
    else if (queue->head->next == queue->head)
    {
        TCB_t * temp = queue->head;
        queue->head = NULL;
        return temp;
    }
    else
    {
        TCB_t * temp = queue->head;
        TCB_t * tail = queue->head->prev;
        if(queue->head->next == queue->head)
        {
            queue->head = NULL;
        }
        else
        {
            queue->head = queue->head->next;
            queue->head->prev = tail;
            tail->next = queue->head;
        }
        return temp;
    }
}

void RotateQ(struct Queue * queue)
{
    queue->head = queue->head->next;
}

void FreeQueue(struct Queue * queue)
{
    TCB_t * head;
    while(head != NULL)
    {
        TCB_t * temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}