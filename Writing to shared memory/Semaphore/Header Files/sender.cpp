#include "sender.hpp"


Sender::Sender()
{
    setUp();
}

Sender::~Sender()
{
    Transfer::cleanUp();
}

// Setup the sender
int Sender::setUp()
{    
    if ((semNewData = sem_open(SEM_NEWDATA, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return (1);
    }


    if ((fileDir = shm_open(FILENAME, O_CREAT | O_RDWR, 0600)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n"
                  << errno;
        return(1);
    }

    if ((ftruncate(fileDir, sizeof(struct memory_data))) == -1)
    {
        std::cout << "truncate fail\n";
        return (1);
    }

    if ((addr = (struct memory_data *)mmap(NULL, sizeof(struct memory_data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n"
                  << errno << std::endl;
        return (1);
    }

    return (0);
}


int Sender::run()
{    
    // Reset the time
    time(&my_time);                    // Current time put into my_time
    ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
    outputTime = asctime(ltime); // Takes in a pointer, converts to string

    genData();


    if ((sem_post(semNewData)) == -1) // Signal new information, unblock
    {
        std::cout << "sem post new data failure loop\n";
        return (1);
    }

    std::cout << "Sending\n";
    display();
    std::cout << "\n\n";

    return(0);
}


void Sender::genData()
{
    int randId, randData;

    randId = rand() % 255;
    // Random number between 0 and 255

    addr->id = randId;

    for (int p = 0; p < ARR_SIZE; p++)
    {
        randData = rand() % 255;
        addr->arr[p] = randData;
    }


}
