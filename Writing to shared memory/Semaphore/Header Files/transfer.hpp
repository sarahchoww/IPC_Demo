// Interface for sender and receiver
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <ctime>
#include <sys/types.h>
#include <semaphore.h>

#include <errno.h>

#define SEM_NAME "/semTest" // Same name to share semaphores
#define SEM_NEWDATA "/signal-new-data"
#define FILENAME "/testSHM"
#define ARR_SIZE 6

#pragma once

class Transfer
{
protected:
   struct memory_data
    {
        int id;
        int arr[ARR_SIZE];
    };

    int fileDir;

    size_t sizeTime, sizeBuf;
    //const char *fileName = "/testSHM"; // Pointing to where /testSHM is in memory

    time_t my_time;
    char *outputTime = nullptr;
    struct tm *ltime; // Local time

    struct memory_data *addr;
    // Set size of addr

    sem_t *semPtr, *semNewData;

 

public:

    virtual int setUp() = 0;
    virtual int run() = 0;
    void cleanUp();
    void display();

};
