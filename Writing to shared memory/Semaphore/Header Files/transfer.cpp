
#include "transfer.hpp"




void Transfer::display()
{

    std::cout << outputTime;

    std::cout << "Sending ID: " << std::dec << addr->id
              << "\t\t\t\t\tIn hex: 0x" << std::hex << addr->id << std::endl;

    std::cout << "Sending data: ";

    for (int q = 0; q < (ARR_SIZE * 2); q++)
    {
        if (q < (ARR_SIZE))
        {
            std::cout << "[" << std::dec << addr->arr[q] << "]";
        }
        else if (q == ARR_SIZE)
        {
            std::cout << "\tIn hex: ";
        }

        if (q >= (ARR_SIZE))
        {
            std::cout << "0x" << std::hex << addr->arr[q - ARR_SIZE] << " ";
        }
    }
}

void Transfer::cleanUp()
{
    if (munmap(addr, sizeof(struct memory_data)) == -1)
    {
        std::cout << "munmap failed\n";
    }

    close(fileDir);

    shm_unlink("/testSHM");

    sem_unlink(SEM_NAME);
    sem_unlink(SEM_NEWDATA);
    
}
