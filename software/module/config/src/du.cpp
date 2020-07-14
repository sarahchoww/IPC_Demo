#include <config/du.hpp>

// cVar is for config variables
// iterator is for message variables

DU::DU(configVars &cVar, memory_data &iterator, bitPackCP_t *&sendBit)
{
    std::cout << "section type\n";
    iterator.sectionType = 1;
    //sendBit->sectionType = swapBits(iterator.sectionType);

    std::cout << "startPrbc\n";
    iterator.startPrbc = 0; // For now *******
    //sendBit->startPrbc = swapBits(iterator.startPrbc);

    if (cVar.RATtype == "LTE") // LTE
    {
        numOfFrames = 256; // Follow up
        numOfSubframes = 10;
        numOfSlots = 2;

        // number of symbols
        if (cVar.prefixType == "Normal") // Normal
        {
            numOfSyms = 7;
        }
        else // Extended
        {
            numOfSyms = 6;
        }

        // number of PRBs
        if (cVar.bandwidth == 1.4)
        {
            iterator.numPrbc = 6;
        }
        else
        {
            iterator.numPrbc = cVar.bandwidth * 5;
        }

        std::cout << "numPRBC\n";
        //sendBit->numPrbc = iterator.numPrbc;
        //sendBit->numPrbc = swapBits(iterator.numPrbc);
    }
    else // NR
    {
        std::cout << "RATtype:\t" << cVar.RATtype << std::endl;
    }
}

int DU::rotateGrid(memory_data &iterator, Transfer *&process, bitPackCP_t *&sendBit)
{
    int runResult;
    for (iterator.frameId = 0; (int)iterator.frameId < numOfFrames; iterator.frameId++)
    {
        std::cout << "frameID\n";
        //sendBit->frameId = swapBits(iterator.frameId);

        for (iterator.subframeId = 0; (int)iterator.subframeId < numOfSubframes; iterator.subframeId++)
        {
            std::cout << "subframeID\n";
            //sendBit->subframeId = swapBits(iterator.subframeId);

            for (iterator.slotId = 0; (int)iterator.slotId < numOfSlots; iterator.slotId++)
            {
                std::cout << "slotID\n";
                //sendBit->slotId = swapBits(iterator.slotId);

                // Send C-Plane message

                for (iterator.startSymbolid = 0; (int)iterator.startSymbolid < numOfSyms; iterator.startSymbolid++)
                {
                    // Send U-Plane message;
                    std::cout << "start symbol id\n";
                    //sendBit->startSymbolid = swapBits(iterator.startSymbolid);

                    /*
                    for (int blockPRBc = (int)sendBit->startPrbc; blockPRBc < (int)sendBit->numPrbc; blockPRBc++) // 12 RE per PRB
                    {
                        for (int elePRBc = 0; elePRBc < 12; elePRBc++)
                        {
                            //std::cout << "RESOURCE BLOCK: " << blockPRBc << std::endl;

                            //std::cout << "RESOURCE ELEMENT: " << elePRBc << std::endl;
                        }
                    }
*/
                    runResult = process->run(iterator, sendBit);
                    if (runResult == 1) // Failed
                    {
                        std::cout << "run failed\n";
                        return (1);
                    }
                    else if (runResult == 2) // Timed out
                    {
                        return (0);
                    }
                }
            }
        }
    }
    return (0);
}

unsigned int DU::swapBits(unsigned int &num) // For unsigned int values
{
    std::cout << "value\t" << std::dec << (num) << std::endl;

    std::bitset<8> x(num);
    std::cout << "before\t" << x << std::endl;

    num = (num >> 4) | (num << 4);
    num = ((num & 0xCC) >> 2) | ((num & 0x33) << 2);
    num = ((num & 0xAA) >> 1) | ((num & 0x55) << 1);

    x = num;
    std::cout << "after\t" << x << std::endl;

    std::cout << std::endl;
    return (num);
}
