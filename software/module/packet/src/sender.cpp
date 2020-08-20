#include <packet/sender.hpp>

Sender::Sender(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue, data);
    //setUp(data);
}

// Setup the sender
int Sender::setUp(uint8_t **data)
{

    //std::cout << "mmap 1\t" << &(*data) << "\tvalue\t" << *data << std::endl;
    printf("mmap1: Address: %p\tValue:  %p\n", &(*data), *data);

    if ((*data = (uint8_t *)malloc(sizeof(struct ether_header) + sizeof(struct ecpri_header) + sizeof(bitPackCP_t) + sizeof(bitPackUP_t))) == NULL)
    {
        std::cout << "malloc failed\n";
        return (RETURN_FAILURE);
    }

    //std::cout << "mmap 2\t" << &(*data) << "\tvalue\t" << *data << std::endl;
    printf("mmap2: Address: %p\tValue:  %p\n", &(*data), *data);

    return (0);
}

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
