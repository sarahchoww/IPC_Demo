#include "sender.hpp"

Sender::Sender()
{
    Transfer::setUp();
    setUp();
}

Sender::~Sender()
{
    Transfer::cleanUp();
}

// Setup the sender
int Sender::setUp()
{
    if ((addr = (struct memory_data *)mmap(NULL, sizeof(struct memory_data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return (1);
    }

    return (0);
}

int Sender::run()
{
    // Reset the time
    time(&my_time);              // Current time put into my_time
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
    std::cout << "\n";

    std::cout << "Waiting for data to be received\n\n";

    if ((sem_wait(semReceived)) == -1) // Wait for signal data was received
    {
        std::cout << "sem wait received failed\n";
        return (1);
    }

    return (0);
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
