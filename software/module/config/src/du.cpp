#include <config/du.hpp>

void DU::setData()
{
    if (RATtype == "LTE") // LTE
    {
        numOfFrames = 256; // Follow up
        numOfSubframes = 10;
        numOfSlots = 2;
        
        // number of symbols
        if (prefixType == "Normal") // Normal
        {
            numOfSyms = 7;
        }
        else // Extended
        {
            numOfSyms = 6;
        }

        // number of PRBs
        if (bandwidth == 1.4)
        {
            
        }


    }
    else // NR
    {
        NULL;
    }
}

void DU::iterateData()
{
    rotateGrid();

    std::cout << "from struct\t" << iterator.payloadVersion << std::endl;
}

void DU::rotateGrid()
{
    std::cout << "entered func\n";
    /*
    for(iterator.frameId; iterator.frameId < numOfFrames; iterator.frameId++)
    {
        for(iterator.subframeId; iterator.subframeId < numOfSubframes; iterator.subframeId++)
        {
            for(iterator.slotId; iterator.slotId < numOfSlots; iterator.slotId++)
            {
                for(iterator.startSymbolid; iterator.startSymbolid < numOfSyms; iterator.startSymbolid++)
                {
                    NULL;
                }
            }
        }
    }

    */
}