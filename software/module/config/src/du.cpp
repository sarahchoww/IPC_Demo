#include <config/du.hpp>

// cVar is for config variables
// iterator is for message variables

DU::DU(configVars &cVar, memory_data &iterator, bitPack_t *&sendBit)
{
    sendBit->sectionType = 1;
    sendBit->startPrbc = 0; // For now *******

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
    }
    else // NR
    {
        std::cout << "RATtype:\t" << cVar.RATtype << std::endl;
    }
}

int DU::rotateGrid(memory_data &iterator, Transfer *&process, bitPack_t *&sendBit)
{
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

                for (iterator.startSymbolid = 0; (int)iterator.startSymbolid < numOfSyms; iterator.startSymbolid++)
                {
                    // Send U-Plane message;
                    sendBit->numPrbc = iterator.numPrbc;


                    sendBit->startSymbolid = iterator.startSymbolid;

                    for (int countPRBc = 0; countPRBc < 12; countPRBc++) // 12 RE per PRB
                    {
                        std::cout << "RESOURCE ELEMENT: " << countPRBc << std::endl;
                    }

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

                    if (sendBit->startPrbc < sendBit->numPrbc)
                    {
                        sendBit->startPrbc += 1; // Go to next PRB
                        std::cout << "This is PRB number " << sendBit->startPrbc << std::endl;
                    }
                    else
                    {
                        return (0);
                    }
                    

                }
            }
        }
    }
    return (0);
}
