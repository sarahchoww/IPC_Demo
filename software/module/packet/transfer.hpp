#pragma once
#include <config/struct.hpp>

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



#define SEM_NEWDATA "/signal-new-data"
#define SEM_RECEIVED "/wait-received"
#define FILENAME "/testSHM"
#define FILEPATH "/dev/shm/sem."
#define ARR_SIZE 6

class Transfer
{
protected:
    int fileDir;

    time_t my_time;
    char *outputTime = nullptr;
    struct tm *ltime; // Local time


    sem_t *semNewData, *semReceived;

    const char * semNewDataFile;
    const char * semReceivedFile;
    const char * fileID;


 

public: 
    virtual ~Transfer() = default;
    int setUp(int idValue);

    virtual int run(memory_data &iterator, bitPackCP_t *&sendBit) = 0;
    void cleanUpMap(bitPackCP_t *&sendBit);
    void cleanUpFiles(memory_data &iterator);
    const char * arrangeFiles(std::string fileToArrange, int id, int operation);

    void display(bitPackCP_t *&sendBit, memory_data &iterator);
};
