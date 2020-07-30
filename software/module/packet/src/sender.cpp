#include <packet/sender.hpp>

Sender::Sender(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue);
    setUp(data);

}

// Setup the sender
int Sender::setUp(uint8_t **data)
{

    //std::cout << "mmap 1\t" << &(*data) << "\tvalue\t" << *data << std::endl;
    printf("mmap1: Address: %p\tValue:  %p\n", &(*data), *data );

 
    if ((*data = (uint8_t *)mmap(NULL, sizeof(bitPackCP_t) + sizeof(bitPackUP_t), PROT_READ | PROT_WRITE, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return (RETURN_FAILURE);
    }

    //std::cout << "mmap 2\t" << &(*data) << "\tvalue\t" << *data << std::endl;
    printf("mmap2: Address: %p\tValue:  %p\n", &(*data), *data );


    return (0);
}

int Sender::run(memory_data &iterator, uint8_t data[])
{
    std::clock_t start;
    double duration;

    struct timespec timer;

    duration = 0;
    start = std::clock();

    // Reset the time
    time(&my_time);              // Current time put into my_time
    ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
    outputTime = asctime(ltime); // Takes in a pointer, converts to string

    if ((sem_post(semNewData)) == -1) // Signal new information, unblock
    {
        std::cout << "sem post new data failure loop\n";
        return (RETURN_FAILURE);
    }

    std::cout << "Sending\n";
    //display(data);

    std::cout << "Waiting for data to be received\n\n";

    if (clock_gettime(CLOCK_REALTIME, &timer) == -1) // Get current time and store in timer
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    timer.tv_sec += 10; // Add 10 seconds to timer, when to time out

    if ((sem_timedwait(semReceived, &timer)) == -1) // Wait for signal data was received
    {
        if (errno == ETIMEDOUT) // Timed out
        {
            std::cout << "Timed out\n";
            cleanUpFiles(iterator); // Delete files in shared memory
            cleanUpMap(data);
            return (RETURN_TIMEDOUT);
        }
        else // Error
        {
            std::cout << "sem wait received failed\n";
            return (RETURN_FAILURE);
        }
    }
    else
    {
        while (duration < 0.5) // Wait 0.5 seconds
        {
            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            // CLOCKS_PER_SEC is number of clock ticks per second (1 000 000 ticks per second)
            // Take current clock minus clock from start divided by ticks per second
        }
    }

    return (0);
}
