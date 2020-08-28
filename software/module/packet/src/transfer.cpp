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
    UPstruct->iSample = iterator.iSample;
    UPstruct->qSample = iterator.qSample;
    
}



int Transfer::passThroughEncode(uint8_t data[], size_t size)
{
    useEnc.encodeData(data, size, sizeof(ether_header) + sizeof(ecpri_header));

    return (0);
}

int Transfer::passThroughEth(uint8_t data[], size_t size, int msg_type)
{
    if (useTransport.sendEth(data, size, msg_type) == 1)
    {
        return (RETURN_FAILURE);
    }
    
    return(0);
}



