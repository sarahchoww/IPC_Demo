#pragma once
#include <config/struct.hpp>
#include <encDec/encode.hpp>

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


#define RETURN_FAILURE 1
#define RETURN_TIMEDOUT 2
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


    sem_t *semNewData;
    sem_t *semReceived;

    const char * semNewDataFile;
    const char * semReceivedFile;
    const char * fileID;


    //char data[1024]; // For both CP and UP
    //bitPackUP_t *UPstruct = (struct bitPackUP *) data; // Access UP data but point to data

    Encode useEnc;

public: 

    virtual ~Transfer() = default;

    int setUp(int idValue);
    virtual int run(memory_data &iterator, uint8_t data[]) = 0;
    void display(uint8_t *data);

    const char * arrangeFiles(std::string fileToArrange, int id, int operation);
    void cleanUpMap(uint8_t data[]);
    void cleanUpFiles(memory_data &iterator);

    void sendForPack(uint8_t data[], memory_data &iterator, bitPackCP_t *CPstruct, bitPackUP_t *UPstruct);
    //void sendForPack(bitPackUP_t *&sendBit, memory_data &iterator);

    void passThroughEncode(uint8_t data[], size_t size);

};
