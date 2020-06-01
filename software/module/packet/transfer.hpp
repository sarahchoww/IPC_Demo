// Interface for sender and receiver
#include <iostream>
#include <sys/mman.h> // mmap flags
#include <fcntl.h> // flags
#include <unistd.h> // ftruncate
#include <ctime> // localtime and asctime
#include <sys/types.h> // time_t
#include <semaphore.h> // sem
#include <signal.h> // For ctrl-c
#include <string.h>
#include <stdio.h>

#define SEM_NEWDATA "/signal-new-data"
#define SEM_RECEIVED "/wait-received"
#define FILENAME "/testSHM"
#define FILEPATH "/dev/shm/sem."
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

    time_t my_time;
    char *outputTime = nullptr;
    struct tm *ltime; // Local time

    struct memory_data *addr;

    sem_t *semNewData, *semReceived;

 

public:

    virtual ~Transfer() = default;
    int setUp();
    virtual int run() = 0;
    void cleanUpMap();
    void cleanUpFiles ();
    void deleteSemFiles(char deleteFile[]);
    void display();
};
