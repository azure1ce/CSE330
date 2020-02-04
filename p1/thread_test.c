/*
Assignment: 1
Class: CSE330
Name: Jingming Tan
Date:07/17/2019
*/

#include <unistd.h>
#include "threads.h"

TCB_t *RunQ = 0;
int globalVariable1 = 1;
int globalVariable2 = 7;
void infiniteLoop1();
void infiniteLoop2();
void infiniteLoop3();
void infiniteLoop4();

int main()
{
    printf("GlobalVariable1=1\nGlobalVariable2=1\nLocalVariable1=1\nLocalVariable2=17\nLocalVariable3=1\nLocalVariable4=700\n");
    start_thread(infiniteLoop1);
    start_thread(infiniteLoop2);
    start_thread(infiniteLoop3);
    start_thread(infiniteLoop4);
    run();
    return 0;
}

void infiniteLoop1()
{
    int count = 1;

    while(1)
    {
        printf("\nTest1 - %p Add 7", RunQ);
        globalVariable1 = globalVariable1 + 7;
        count = count + 7;
        printf("\nLocalVariable1 = %d   GlobalVariable1 = %d\n" , count, globalVariable1);
        sleep(1);
        yield();
    }
}

void infiniteLoop2()
{
    int count = 17;

    while(1)
    {
        printf("\nTest2 Thread - %p Minus 7", RunQ);
        globalVariable1  = globalVariable1 - 7;
        count = count - 7;
        printf("\nLocalVariable2 = %d   GlobalVariable1= %d\n" , count, globalVariable1);
        sleep(1);
        yield();
    }
}

void infiniteLoop3()
{
 
    int count = 1;

    while(1)
    {   
        printf("\nTest3 - %p Times 7", RunQ);
        globalVariable2 = globalVariable2 * 7;
        count  = count * 7;
        printf("\nLocalVariable3 = %d   GlobalVariable2 = %d\n" , count, globalVariable2);
        sleep(1);
        yield();
    }
}



void infiniteLoop4()
{
    int count = 700;

    while(1)
    {
        printf("\nTest4 - %p Divide by 7", RunQ);
        globalVariable2 = globalVariable2 / 7;
        count = count / 7;
        printf("\nLocalVariable4 = %d   GlobalVariable2 = %d\n" , count, globalVariable2);
        sleep(1);
        yield();
    }
}

