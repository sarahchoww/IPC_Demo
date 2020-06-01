
#include <packet/transfer.hpp>


void Transfer::display()
{

    std::cout << outputTime;

    std::cout << "ID: " << std::dec << addr->id
              << "\t\t\t\t\tIn hex: 0x" << std::hex << addr->id << std::endl;

    std::cout << "Data: ";

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

int Transfer::setUp()
{   
    if ((semNewData = sem_open(SEM_NEWDATA, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return(1);
    }

    if ((semReceived = sem_open(SEM_RECEIVED, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return(1);
    }

    if ((fileDir = shm_open(FILENAME, O_CREAT | O_RDWR, 0600)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n";
        return(1);
    }


    if ((ftruncate(fileDir, sizeof(struct memory_data))) == -1)
    {
        std::cout << "truncate fail\n";
        return(1);
    }

    return(0);
}

void Transfer::cleanUpMap()
{
    if (munmap(addr, sizeof(struct memory_data)) == -1)
    {
        std::cout << "munmap failed\n";
    }

}


void Transfer::deleteSemFiles (char deleteFile[])
{

    std::string temp = FILEPATH;

    char rm[temp.length() + strlen(deleteFile)] = FILEPATH; // variable for file path to shared memory, size of both strings

    strcat(rm, deleteFile); // concatenate file path and file name into "rm"


    if (remove(rm) != 0)
    {
        std::cout << "remove error\n"
                  << errno;
    }
}


void Transfer::cleanUpFiles()
{
    shm_unlink(FILENAME);

    sem_close(semNewData);
    sem_close(semReceived);

  for (int i = 0; i < 2; i++)
    {
        std::string deleteFileName;

        if (i == 1)
        {
            deleteFileName = SEM_NEWDATA;
        }
        else
        {
            deleteFileName = SEM_RECEIVED;

        }
        
        
        char *deleteFile = new char[deleteFileName.length()];

        std::copy(deleteFileName.begin() + 1, deleteFileName.end(), deleteFile); // Copy string to a char, omit the slash

        deleteSemFiles(deleteFile);

        delete[] deleteFile;

    }
}

