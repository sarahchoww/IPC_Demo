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

const char *Transfer::arrangeFiles(std::string fileToArrange, int id, int operation)
{
    // Rearrange / append characters and put into const char *
    // Operation 1 : create file
    // Operation 2 : delete file

    int numOffset = 0; // Offset when setting up to delete, need to rid of first slash

    char *fileName = new char[fileToArrange.length()];

    if (operation == 2)
    {
        numOffset = 1;
    }

    std::copy(fileToArrange.begin() + numOffset, fileToArrange.end(), fileName); // Copy string to a char*, omit the slash

    if (operation == 1)
    {
        const char *charID = (std::to_string(id)).c_str();
        // Convert ID to const char *

        strcat(fileName, charID); // Add id to end of file name

        return fileName; // Return file name with id
    }
    else if (operation == 2)
    {
        std::string temp = FILEPATH;                            // Put filepath in a string
        char edit[temp.length() + strlen(fileName)] = FILEPATH; // Create new char with filepath in it
        strcat(edit, fileName);                                 // concatenate file path and file name into "edit"

        if (remove(edit) != 0)
        {
            std::cout << "remove error\n";
        }
    }
    return NULL;
}


int Transfer::setUp(int id)
{

    semNewDataFile = arrangeFiles(SEM_NEWDATA, id, 1);
    semReceivedFile = arrangeFiles(SEM_RECEIVED, id, 1);
    fileID = arrangeFiles(FILENAME, id, 1);


    if ((semNewData = sem_open(semNewDataFile, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return (1);
    }

    if ((semReceived = sem_open(semReceivedFile, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem received failed\n";
        return (1);
    }

    if ((fileDir = shm_open(fileID, O_CREAT | O_RDWR, 0600)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n";
        return (1);
    }

    if ((ftruncate(fileDir, sizeof(struct memory_data))) == -1)
    {
        std::cout << "truncate fail\n";
        return (1);
    }

    return (0);
}

void Transfer::cleanUpMap()
{
    if (munmap(addr, sizeof(struct memory_data)) == -1)
    {
        std::cout << "munmap failed\n";
    }
}

void Transfer::cleanUpFiles()
{
    shm_unlink(fileID);

    sem_close(semNewData);
    sem_close(semReceived);

    arrangeFiles(semNewDataFile, (addr->id), 2);
    arrangeFiles(semReceivedFile, (addr->id), 2);
}
