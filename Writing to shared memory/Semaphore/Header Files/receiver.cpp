#include "receiver.hpp"

Receiver::Receiver()
{
    setUp();
}

Receiver::~Receiver()
{
    Transfer::cleanUp();
}

int Receiver::setUp()
{
    
    if ((semPtr = sem_open(SEM_NAME, O_CREAT, 0400, 0)) == SEM_FAILED) // Access the semaphore
    {
        std::cout << "sem open failed\n";
        return (1);
    }

    if ((semNewData = sem_open(SEM_NEWDATA, O_CREAT, 0400, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return (1);
    }

    if ((fileDir = shm_open(FILENAME, O_CREAT | O_RDWR, 0400)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n"
                  << errno;
        exit(1);
    }


    if ((ftruncate(fileDir, sizeof(struct memory_data))) == -1)
    {
        std::cout << "truncate fail\n";
        return (1);
    }


    if ((addr = (struct memory_data *)mmap(NULL, sizeof(struct memory_data), PROT_READ, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n"
                  << errno << std::endl;
        return (1);
    }

    if ((sem_post(semPtr)) == -1) // Unblocks sem for client to acknowledge
    {
        std::cout << "sem post failed\n";
        return (1);
    }

    return (0);
}


int Receiver::run ()
{
    if ((sem_trywait(semNewData)) == -1) // Tries to access signal, if not possible, returns to loop
    {
        std::cout << "sem wait new data failure\n" << errno <<std::endl;
        return (1);
    }

    // Reset the time
    time(&my_time);                       // Current time put into my_time
    ltime = localtime(&my_time); // Return the 'struct tm' representation of timer in local time zone
    outputTime = asctime(ltime);   // Takes in a pointer, converts to string

    display();

    std::string test;
    std::cin >> test;


    return (0);
}
