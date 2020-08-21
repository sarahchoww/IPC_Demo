#include <packet/transfer.hpp>


int Transfer::setUp(int idValue, uint8_t **data)
{

    printf("malloc1: Address: %p\tValue:  %p\n", &(*data), *data);

    if ((*data = (uint8_t *)malloc(sizeof(struct ether_header) + sizeof(struct ecpri_header) + sizeof(bitPackCP_t) + sizeof(bitPackUP_t))) == NULL)
    {
        std::cout << "malloc failed\n";
        return (RETURN_FAILURE);
    }

    //std::cout << "mmap 2\t" << &(*data) << "\tvalue\t" << *data << std::endl;
    printf("malloc2: Address: %p\tValue:  %p\n", &(*data), *data);

    return (0);
}


void Transfer::cleanUpFiles(memory_data &iterator, uint8_t **data)
{

    delete *data;

    useTransport.~Transport();


}



// function override, not template
void Transfer::packCP(uint8_t data[], memory_data &iterator, bitPackCP_t *CPstruct, bitPackUP_t *UPstruct)
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

int Transfer::passThroughEncode(uint8_t data[])
{

/*
    // Make dummyIQ
    int num;

    for (int i = 0; i < 32; i++)
    {

        num = rand() % 100;

        buf[i] = 0b00110000;

        if ((num % 5) == 0) // Space
        {
            buf[i] = 0b00100000;
        }

        if (i % 5 == 0) // New line every 4th
        {
            buf[i] = 0b00001010;
        }
    }
*/

    size_t sizeHeader = sizeof(struct ether_header);

    useEnc.encodeData(data, sizeof(bitPackCP_t), sizeof(ether_header) + sizeof(ecpri_header));

    return (0);
}

int Transfer::passThroughEth(uint8_t data[])
{
    if (useTransport.sendEth(data, sizeof(bitPackCP_t)) == 1)
    {
        return (RETURN_FAILURE);
    }
    
    return(0);
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
