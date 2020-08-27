#include <packet/transfer.hpp>


int Transfer::setUp(int idValue, uint8_t **data)
{
    if ((*data = (uint8_t *)malloc(sizeof(struct ether_header) + sizeof(struct ecpri_header) + sizeof(bitPackCP_t) + sizeof(bitPackUP_t))) == NULL)
    {
        std::cout << "malloc failed\n";
        return (RETURN_FAILURE);
    }
    return (0);
}


void Transfer::cleanUpFiles(memory_data &iterator, uint8_t **data)
{

    delete *data;

    useTransport.~Transport();


}



// function override, not template
void Transfer::packStruct(uint8_t data[], memory_data &iterator, bitPackCP_t *CPstruct)
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

}


void Transfer::packStruct(uint8_t data[], memory_data &iterator, bitPackUP_t *UPstruct)
{
    UPstruct->dataDirection = iterator.dataDirection;
    UPstruct->payloadVersion = iterator.payloadVersion;
    UPstruct->filterIndex = iterator.filterIndex;
    UPstruct->frameId = iterator.frameId;
    UPstruct->subframeId = iterator.subframeId;
    UPstruct->slotId = iterator.slotId;
    UPstruct->symbolId = iterator.symbolId;
    UPstruct->sectionId = iterator.sectionId;
    UPstruct->rb = iterator.rb;
    UPstruct->symInc = iterator.symInc;
    UPstruct->startPrbu = iterator.startPrbu;
    UPstruct->numPrbu = iterator.numPrbu;
    UPstruct->udCompHdr = iterator.udCompHdr;
    UPstruct->reserved = iterator.reserved;
    
}



int Transfer::passThroughEncode(uint8_t data[], size_t size)
{

/*
    // Make dummyIQ
    int num;
    char buf[20];

    for (int i = 0; i < 20; i++)
    {

        num = rand() % 100;

        buf[i] = 0b00110000;

        if ((num % 15) == 0) // Space
        {
            buf[i] = 0b00100000;
        }

        if (i % 5 == 0) // New line every 4th
        {
            buf[i] = 0b00001010;
        }
    }

    std::cout << buf;

*/

/*
    for (int i = 0; i < 20; i++)
    {
        float num1, num2;

        num1 = (rand() % 10) / 100; // Between 0 and 10, divide by 100 for decimal
        num2 = (rand() % 10) / 100;

        std::pair <std::float,float> newPair (num1, num2);  
    }

    std::pair <std::float, float> arrIQ[20];  
*/
    


    // Function overload
    useEnc.encodeData(data, size, sizeof(ether_header) + sizeof(ecpri_header));

    return (0);
}

// Fusnction overload
int Transfer::passThroughEth(uint8_t data[], size_t size)
{
    if (useTransport.sendEth(data, size) == 1)
    {
        return (RETURN_FAILURE);
    }
    
    return(0);
}



