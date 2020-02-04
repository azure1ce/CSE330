/*
Jingming Tan
CSE330-Operation Systems-2019-Summer
*/
#include <stdio.h>
#include <unistd.h> // Used for sleep()
#include "sem.h"

#define true 1
#define false 0

#define METHOD_1 1
#define METHOD_2 2

#define NUM_RESOURCES 1 // Should be LESS than the number of threads running, to create "competition"
#define BUFFER_SIZE 5
#define SLEEP_TIME 1 // in seconds

enum ERRORS{
    ERROR_INVALID_INPUT = 10,
    ERROR_UNDEFINED
};

// Method 1 stuff - Multithreading w/ global var
void Method_1();
int global = 0;
Semaphore * s;
void func1();
void func2();
void func3();

// Method 2 stuff - Producer/Consumer
void Method_2();
int buffer[BUFFER_SIZE];
int in, out = 0;
Semaphore * full;
Semaphore * empty;
Semaphore * mutexC;
Semaphore * mutexP;
void producer1();
void producer2();
void consumer1();
void consumer2();

// Other method forward declarations
void printbuffer();
void error(int error_message);
int isValidInput(int num);

int main()
{
    runQ = InitQueue();

    printf("\n\n");
    printf("Method 1: \n"
                   "Each thread is an infinite loop, and has\n"
                   "a critical section using a mutex semaphore.\n"
                   "The thread gets into the critical section,\n"
                   "prints the values of the global and local\n"
                   "variables (like project 1), sleeps and exits\n"
                   "the critical section. Then it prints a message\n"
                   "and sleeps and then repeats.\n\n");
    printf("Method 2: \n"
                   "Write a producer and consumer solution, using the\n"
                   "code given in class (see notes). Run 2 producers\n"
                   "and 2 consumers. You will have to work out some\n"
                   "details. If you choose to do this you really\n"
                   "should do method 1 first. Also, doing this will\n"
                   "make it easier for you to do project 4.\n\n");
    printf("Which method would you like to perform? (type '1' or '2') \n");

    int c = getchar() - 48; // ASCII for 0 is 48
    if (!isValidInput(c))
    {
        error(ERROR_INVALID_INPUT);
    }

    switch(c)
    {
        case METHOD_1:
            s = InitSem(NUM_RESOURCES);
            Method_1();
            break;
        case METHOD_2:
            full = InitSem(0); // TODO Why is this initialized to zero???
            empty = InitSem(BUFFER_SIZE);
            mutexP = InitSem(1);
            mutexC = InitSem(1);
            // Initialize buffer
            int i;
            for (i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = 0;
            }
            Method_2();
            break;
        default:
            error(ERROR_UNDEFINED);
            break;
    }
    return 0;
}

void Method_1()
{
    printf("Method 1 starting\n\n");

    start_thread(func1);
    start_thread(func2);
    start_thread(func3);

    run();

    // Control never reaches this point
    FreeQueue(runQ);
    FreeSemaphore(s);
}

void Method_2()
{
    printf("Method 2 starting\n\n");

    start_thread(producer1);
    start_thread(producer2);
    start_thread(consumer1);
    start_thread(consumer2);

    run();
}

void func1()
{
    while(true)
    {
        P(s); // Critical section start
        global++;
        printf("Function 1: %d\n", global);
        sleep(SLEEP_TIME);
        V(s); // Critical section end
    }
}

void func2()
{
    while(true)
    {
        P(s); // Critical section start
        global++;
        printf("Function 2: %d\n", global);
        sleep(SLEEP_TIME);
        V(s); // Critical section end
    }
};

void func3()
{
    while(true)
    {
        P(s); // Critical section start
        global++;
        printf("Function 3: %d\n", global);
        sleep(SLEEP_TIME);
        V(s); // Critical section end
    }
};

void producer1()
{
    while(true)
    {
        P(empty);
        P(mutexP); // Begin critical section

        buffer[in] = 1;
        in = (in + 1) % BUFFER_SIZE;

        printf("Producer 1: added   \t");
        printbuffer();
        sleep(SLEEP_TIME);

        V(mutexP); // End critical section
        V(full);
    }
}

void producer2()
{
    while(true)
    {
        P(empty);
        P(mutexP); // Begin critical section

        buffer[in] = 1;
        in = (in + 1) % BUFFER_SIZE;

        printf("Producer 2: added   \t");
        printbuffer();
        sleep(SLEEP_TIME);

        V(mutexP); // End critical section
        V(full);
    }
}

void consumer1()
{
    while(true)
    {
        P(full);
        P(mutexC); // Begin critical section

        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumer 1: removed \t");
        printbuffer();
        sleep(SLEEP_TIME);

        V(mutexC); // End critical section
        V(empty);
    }
}

void consumer2()
{
    while(true)
    {
        P(full);
        P(mutexC); // Begin critical section

        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumer 2: removed \t");
        printbuffer();
        sleep(SLEEP_TIME);

        V(mutexC); // End critical section
        V(empty);
    }
}

void printbuffer()
{
    int i;
    for(i = 0; i < BUFFER_SIZE; i++){
        printf("%d\t", buffer[i]);
    }
    printf("\n");
}

void error(int error_message)
{
    switch(error_message)
    {
        case ERROR_INVALID_INPUT:
            printf("Invalid input, program terminating with error "
                           "code %d", ERROR_INVALID_INPUT);
            exit(ERROR_INVALID_INPUT);
        default:
            printf("Undefined error, program terminating with error"
                           "code %d", ERROR_UNDEFINED);
            exit(ERROR_UNDEFINED);
    }
}

int isValidInput(int num)
{
    switch(num)
    {
        case METHOD_1:
            return true;
        case METHOD_2:
            return true;
        default:
            return false;
    }
}