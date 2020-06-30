#include <packet/transfer.hpp>
#include <vector>

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
            std::cout << "remove error on " << edit << "\n";
        }
    }
    return NULL;
}


int Transfer::setUp(int idValue)
{
    semReceivedFile = arrangeFiles(SEM_RECEIVED, idValue, 1);
    semNewDataFile = arrangeFiles(SEM_NEWDATA, idValue, 1);
    fileID = arrangeFiles(FILENAME, idValue, 1);


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

    if ((ftruncate(fileDir, sizeof(bitPack_t))) == -1)
    {
        std::cout << "truncate fail\n";
        return (1);
    }

    return (0);
}

void Transfer::cleanUpMap(bitPack_t *&sendBit)
{
    if (munmap(sendBit, sizeof(bitPack_t)) == -1)
    {
        std::cout << "munmap failed\n";
    }
}

void Transfer::cleanUpFiles(memory_data &iterator)
{
    shm_unlink(fileID);

    sem_close(semNewData);
    sem_close(semReceived);

    arrangeFiles(semNewDataFile, (iterator.id), 2);
    arrangeFiles(semReceivedFile, (iterator.id), 2);
}


void Transfer::display(bitPack *&sendBit)
{
    std::cout << "DATADIRECTION: " << sendBit->dataDirection;
    std::cout << "\nPAYLOADVER: " << sendBit->payloadVersion;
    std::cout << "\nNUMOFPRB: " << sendBit->numPrbc;
    std::cout << "\nFRAMEID: " << sendBit->frameId;
    std::cout << "\nSUBFRAMEID: " << sendBit->subframeId;
    std::cout << "\nSLOTID: " << sendBit->slotId;
    std::cout << "\nSTARTSYMBID: "<< sendBit->startSymbolid << "\n\n";
}