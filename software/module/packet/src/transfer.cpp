#include <packet/transfer.hpp>
#include <vector>

const char *Transfer::arrangeFiles(std::string fileToArrange, int id, int operation)
{
    // Rearrange / append characters and put into const char *
    // Operation 1 : create file
    // Operation 2 : delete file

    const char *holderVar;

    if (operation == 1)
    {
        fileToArrange.erase(0, 1); // Erase pos 0, len 1 - the backslash
    }

    char *fileName = new char[fileToArrange.length()];

    holderVar = fileToArrange.c_str(); // Convert string to const char *

    strcpy(fileName, holderVar); // Copy data from holderVar to fileName, now a char *

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
            std::cout << "remove error on \t\t" << edit << "\n";
        }
    }

    return NULL;
}

int Transfer::setUp(int idValue)
{
    semNewDataFile = arrangeFiles(SEM_NEWDATA, idValue, 1);
    semReceivedFile = arrangeFiles(SEM_RECEIVED, idValue, 1);
    fileID = arrangeFiles(FILENAME, idValue, 1);

    if ((semNewData = sem_open(semNewDataFile, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem new data failed\n";
        return (RETURN_FAILURE);
    }

    if ((semReceived = sem_open(semReceivedFile, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        std::cout << "sem received failed\n";
        return (RETURN_FAILURE);
    }

    if ((fileDir = shm_open(fileID, O_CREAT | O_RDWR, 0600)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n";
        return (RETURN_FAILURE);
    }

    if ((ftruncate(fileDir, sizeof(bitPackCP_t) + sizeof(bitPackUP_t))) == -1)
    {
        std::cout << "truncate fail\n";
        return (RETURN_FAILURE);
    }

    return (0);
}

void Transfer::cleanUpMap(uint8_t data[])
{
    if (munmap(data, sizeof(bitPackCP_t) + sizeof(bitPackUP_t)) == -1)
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

/*
void Transfer::display(uint8_t *data)
{
    std::cout << "\nNUMOFPRB: " << data[];
    std::cout << "\nFRAMEID: " << data[];
    std::cout << "\nSUBFRAMEID: " << data[];
    std::cout << "\nSLOTID: " << data[];
    std::cout << "\nSTARTSYMBID: " << data[] << "\n\n";
}
*/

// function override, not template
void Transfer::sendForPack(uint8_t data[], memory_data &iterator, bitPackCP_t *CPstruct, bitPackUP_t *UPstruct)
{

    CPstruct->dataDirection = iterator.dataDirection;
    CPstruct->payloadVersion = iterator.payloadVersion;
    CPstruct->filterIndex = iterator.filterIndex;
    CPstruct->frameId = iterator.frameId;
    CPstruct->subframeId = iterator.subframeId;
    CPstruct->slotId = iterator.slotId;
    CPstruct->startSymbolid = iterator.startSymbolid;
    CPstruct->numberOfsections = iterator.numberOfsections;
    CPstruct->sectionType = iterator.sectionType;
    CPstruct->udCompHdr = iterator.udCompHdr;
    CPstruct->reserved = iterator.reserved;
    CPstruct->sectionId = iterator.sectionId;
    CPstruct->rb = iterator.rb;
    CPstruct->symInc = iterator.symInc;
    CPstruct->startPrbc = iterator.startPrbc;
    CPstruct->numPrbc = iterator.numPrbc;
    CPstruct->reMask = iterator.reMask;
    CPstruct->numSymbol = iterator.numSymbol;
    CPstruct->ef = iterator.ef;
    CPstruct->beamId = iterator.beamId;



    passThroughEncode(data, sizeof(bitPackCP_t));

}

void Transfer::passThroughEncode(uint8_t data[], size_t size)
{
    useEnc.encodeData(data, size);
}

/*
void Transfer::sendForPack(bitPackUP_t *&sendBitCP, memory_data &iterator)
{
    // fix variable
    sendBitCP->dataDirection = iterator.dataDirection;
    sendBitCP->payloadVersion = iterator.payloadVersion;
    sendBitCP->filterIndex = iterator.filterIndex;
    sendBitCP->frameId = iterator.frameId;
    sendBitCP->subframeId = iterator.subframeId;
    sendBitCP->slotId = iterator.slotId;
    sendBitCP->startSymbolid = iterator.startSymbolid;
    sendBitCP->numberOfsections = iterator.numberOfsections;
    sendBitCP->sectionType = iterator.sectionType;
    sendBitCP->udCompHdr = iterator.udCompHdr;
    sendBitCP->reserved = iterator.reserved;
    sendBitCP->sectionId = iterator.sectionId;
    sendBitCP->rb = iterator.rb;
    sendBitCP->symInc = iterator.symInc;
    sendBitCP->startPrbc = iterator.startPrbc;
    sendBitCP->reMask = iterator.reMask;
    sendBitCP->numSymbol = iterator.numSymbol;
    sendBitCP->ef = iterator.ef;
    sendBitCP->beamId = iterator.beamId;

    useEnc.encodeData(data, sizeof(bitPackUP_t));
    */
//}

