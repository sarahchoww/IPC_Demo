#include <config/du.hpp>

// cVar is for config variables
// iterator is for message variables

DU::DU(configVars &cVar, memory_data &iterator, bitPack_t *&sendBit)
{
    sendBit->sectionType = 1;
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
        if (cVar.bandwidth == 5)
        {
            iterator.numPrbc = 25;
        }
    }
    else // NR
    {
        std::cout << "RATtype:\t" << cVar.RATtype << std::endl;
    }
}

int DU::rotateGrid(memory_data &iterator, Transfer *&process, bitPack_t *&sendBit)
{
    int count = 0;
    int runResult;

    for (iterator.frameId = 0; (int)iterator.frameId < numOfFrames; iterator.frameId++)
    {
        sendBit->frameId = iterator.frameId;

        for (iterator.subframeId = 0; (int)iterator.subframeId < numOfSubframes; iterator.subframeId++)
        {
            sendBit->subframeId = iterator.subframeId;

            for (iterator.slotId = 0; (int)iterator.slotId < numOfSlots; iterator.slotId++)
            {
                sendBit->slotId = iterator.slotId;

                // Send C-Plane message
                runResult = process->run(iterator, sendBit);
                if (runResult == 1) // Failed
                {
                    std::cout << "run failed\n";
                    return (1);
                }
                else if (runResult == 2) // Timed out
                {
                    return(0);
                }

                for (iterator.startSymbolid = 0; (int)iterator.startSymbolid < numOfSyms; iterator.startSymbolid++)
                {
                    // Send U-Plane message;
                    count++;
                }
            }
        }
    }
    return (0);
}
