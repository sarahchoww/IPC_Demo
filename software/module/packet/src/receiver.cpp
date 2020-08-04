#include <packet/receiver.hpp>

Receiver::Receiver(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue);
    setUp(data);
}

int Receiver::setUp(uint8_t **data)
{

    if ((*data = (uint8_t *)mmap(NULL, sizeof(bitPackCP_t) + sizeof(bitPackUP_t), PROT_READ | PROT_WRITE, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return (RETURN_FAILURE);
    }

    return (0);
}

int Receiver::run(memory_data &iterator, uint8_t data[])
{
    struct timespec timer;

    if (clock_gettime(CLOCK_REALTIME, &timer) == -1) // Get current time and store in timer
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    timer.tv_sec += 10; // Add 10 seconds to timer, when to time out

    std::cout << "Waiting for data\n";


/*
    if ((sem_timedwait(semNewData, &timer)) == -1) // Wait for signal
    {
        if (errno == ETIMEDOUT) // Timed out
        {
            std::cout << "Timed out\n";
            cleanUpFiles(iterator); // Delete files in shared memory
            cleanUpMap(data);
            return(RETURN_TIMEDOUT);
        }
        else // Error
        {
            std::cout << "sem wait new data failure\n"
                      << errno << std::endl;
            return (RETURN_FAILURE);
        }
    }
*/

    if ((sem_wait(semNewData)) == -1) // Wait for signal
    {
            std::cout << "sem wait new data failure\n"
                      << errno << std::endl;
            return (RETURN_FAILURE);
    }
    else
    {

        // Reset the time
        time(&my_time);              // Current time put into my_time
        ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
        outputTime = asctime(ltime); // Takes in a pointer, converts to string

        std::cout << "Receiving\n";



        if (passThroughEncode(data, sizeof(bitPackCP_t)) == 1)
        {
            return(RETURN_FAILURE);
        } 



        if ((sem_post(semReceived)) == -1) // Notify data has been received
        {
            std::cout << "Post notify failed\n";
            return (RETURN_FAILURE);
        }
    }

    return (0);
}
