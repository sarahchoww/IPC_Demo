#include <packet/receiver.hpp>

Receiver::Receiver(int idValue, bitPackCP_t *&sendBit)
{
    Transfer::setUp(idValue);
    setUp(idValue, sendBit);
}

int Receiver::setUp(int idValue, bitPackCP_t *&sendBit)
{

    if ((sendBit = (bitPackCP_t *)mmap(NULL, sizeof(bitPackCP_t), PROT_READ, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return (1);
    }

    return (0);
}

int Receiver::run(memory_data &iterator, bitPackCP_t *&sendBit)
{
    struct timespec timer;

    if (clock_gettime(CLOCK_REALTIME, &timer) == -1) // Get current time and store in timer
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    timer.tv_sec += 10; // Add 10 seconds to timer, when to time out

    std::cout << "Waiting for data\n";

    if ((sem_timedwait(semNewData, &timer)) == -1) // Wait for signal
    {
        if (errno == ETIMEDOUT) // Timed out
        {
            std::cout << "Timed out\n";
            cleanUpFiles(iterator); // Delete files in shared memory
            cleanUpMap(sendBit);
            return(2);
        }
        else // Error
        {
            std::cout << "sem wait new data failure\n"
                      << errno << std::endl;
            return (1);
        }
    }
    else
    {

        // Reset the time
        time(&my_time);              // Current time put into my_time
        ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
        outputTime = asctime(ltime); // Takes in a pointer, converts to string

        std::cout << "Receiving\n";
        display(sendBit, iterator);

        if ((sem_post(semReceived)) == -1) // Notify data has been received
        {
            std::cout << "Post notify failed\n";
            return (1);
        }
    }

    return (0);
}
