#include <packet/sender.hpp>

Sender::Sender(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue, data);
}

// Main purpose is to have a 0.5 second delay
int Sender::run(memory_data &iterator, uint8_t data[])
{
    std::clock_t start;
    double duration;

    struct timespec timer;

    duration = 0;
    start = std::clock();

    std::cout << "Sending\n";


    if (clock_gettime(CLOCK_REALTIME, &timer) == -1) // Get current time and store in timer
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    while (duration < 0.5) // Wait 0.5 seconds
    {
        duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        // CLOCKS_PER_SEC is number of clock ticks per second (1 000 000 ticks per second)
        // Take current clock minus clock from start divided by ticks per second
    }

    // Add in clean up - ctrl c signal interrupt

    return (0);
}
