#include "receiver.hpp"

Receiver::Receiver()
{
    Transfer::setUp();
    setUp();
}

Receiver::~Receiver()
{
    Transfer::cleanUp();
    cleanUp();
}


int Receiver::setUp()
{   
    if ((addr = (struct memory_data *)mmap(NULL, sizeof(struct memory_data), PROT_READ, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return(1);
    }

    return(0);
}


int Receiver::run ()
{
    std::cout << "Waiting for data\n";



    if ((sem_wait(semNewData)) == -1) // Wait for signal
    {
        std::cout << "sem wait new data failure\n" << errno <<std::endl;
        return(1);
    }


    // Reset the time
    time(&my_time);                       // Current time put into my_time
    ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
    outputTime = asctime(ltime);   // Takes in a pointer, converts to string


    std::cout << "Receiving\n";

    display();

    std::cout << "\n\n";

    if ((sem_post(semReceived)) == -1) // Notify data has been received
    {
        std::cout << "Post notify failed\n";
        return(1);
    }


    return(0);
}

void Receiver::cleanUp()
{
    shm_unlink(FILENAME);

    sem_close(semNewData);
    sem_close(semReceived);

    remove("/dev/shm/sem.signal-new-data");
    remove("/dev/shm/sem.wait-received");

    
    
    /*std::string tempRandom = SEM_NEWDATA;
    char deleteFile1[tempRandom.length()] = SEM_NEWDATA;
    char *newCopy1 = nullptr;

    memcpy(newCopy1, deleteFile1 + 1, strlen(deleteFile1)); // rid of the slash at start of name

    std::string temp = FILEPATH;

    char rm1[temp.length() + strlen(newCopy1)] = FILEPATH; // variable for file path to shared memory, size of both strings

    strcat(rm1, newCopy1); // concatenate file path and file name into "rm"

    std::cout << "\n"
              << rm1 << std::endl;

    if (remove(rm1) != 0)
    {
        std::cout << "remove error\n"
                  << errno;
    }

    tempRandom = SEM_RECEIVED;
    char deleteFile[tempRandom.length()] = SEM_RECEIVED;
    char *newCopy = nullptr;

    memcpy(newCopy, deleteFile + 1, strlen(deleteFile)); // rid of the slash at start of name

    char rm[temp.length() + strlen(newCopy)] = FILEPATH; // variable for file path to shared memory, size of both strings

    strcat(rm, newCopy); // concatenate file path and file name into "rm"

    std::cout << "\n"
              << rm << std::endl;

    if (remove(rm) != 0)
    {
        std::cout << "remove error\n"
                  << errno;

    */
}
