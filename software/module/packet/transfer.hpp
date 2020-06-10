#pragma once

// Interface for sender and receiver
#include <iostream>
#include <sys/mman.h> // mmap flags
#include <fcntl.h> // flags
#include <unistd.h> // ftruncate
#include <ctime> // localtime and asctime
#include <sys/types.h> // time_t
#include <semaphore.h> // sem
#include <signal.h> // For ctrl-c
#include <cstring>
#include <stdio.h>
#include <fstream> // Check if file exists in system / try to open the file


#define SEM_NEWDATA "/signal-new-data"
#define SEM_RECEIVED "/wait-received"
#define FILENAME "/testSHM"
#define FILEPATH "/dev/shm/sem."
#define ARR_SIZE 6

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

    const char * semNewDataFile;
    const char * semReceivedFile;
    const char * fileID;


 

public:

    virtual ~Transfer() = default;
    int setUp(int id);

    virtual int run() = 0;
    void cleanUpMap();
    void cleanUpFiles();
    const char * arrangeFiles(std::string fileToArrange, int id, int operation);

    void display();
};
