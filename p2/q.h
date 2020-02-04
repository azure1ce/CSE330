/*
Assignment: 2
Class: CSE330
Name: Jingming Tan
Date:08/01/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include "tcb.h"

TCB_t *NewItem()
{
    TCB_t *tempPtr = (TCB_t*)malloc(sizeof(TCB_t));
    return tempPtr;

}


void InitQueue(TCB_t **head)
{
   *head = NULL;
}

void AddQueue(TCB_t **head, TCB_t *item)
{
    TCB_t *tempPtr = *head;
    if(tempPtr == NULL)
    {
        *head = item;
        (*head)->nextPtr = *head;
        (*head)->prevPtr = *head;
    }

    else
        {
            tempPtr = tempPtr->nextPtr;
            item->nextPtr = tempPtr;
            item->prevPtr = *head;
            tempPtr->prevPtr = item;
            (*head)->nextPtr = item;
        } 

}

TCB_t *DelQueue(TCB_t **head)
{
    TCB_t *tempPtr = *head;

    if(tempPtr != NULL)
    {
        if(tempPtr->nextPtr != tempPtr)
        {
            tempPtr = tempPtr->nextPtr;

            tempPtr->prevPtr->nextPtr = tempPtr->nextPtr;
            tempPtr->nextPtr->prevPtr = tempPtr->prevPtr;
        }
        else
        {
            *head = NULL;
        }
    }
    return tempPtr;
}

void RotateQ(TCB_t **head)
{
    if(*head != NULL)
    {
        TCB_t *tempPtr = *head;
      
        *head = tempPtr->prevPtr;
    }
}

void printQueue(TCB_t *head)
{
    TCB_t *tempPtr = head;
    if(tempPtr == NULL)
    {
        printf("\nThe queue is empty.\n");
    }
    else
    {
        printf("\n%d", tempPtr->number);
        tempPtr = tempPtr->prevPtr;

        while(tempPtr != head)
        {
            printf(" --> %d", tempPtr->number);
            tempPtr = tempPtr->prevPtr;
        }
        printf("\n");
    }
}