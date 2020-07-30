#include <config/du.hpp>

// cVar is for config variables
// iterator is for message variables

void DU::DUsetUp(configVars &cVar, memory_data &iterator)
{


    iterator.sectionType = 1;

    iterator.startPrbc = 0; // For now *******

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

int DU::rotateGrid(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackCP_t *CPstruct, bitPackUP_t *UPstruct)
{

    int runResult;
    for (iterator.frameId = 0; (int)iterator.frameId < numOfFrames; iterator.frameId++)
    {
        for (iterator.subframeId = 0; (int)iterator.subframeId < numOfSubframes; iterator.subframeId++)
        {

            for (iterator.slotId = 0; (int)iterator.slotId < numOfSlots; iterator.slotId++)
            {

                // Send C-Plane message

                for (iterator.startSymbolid = 0; (int)iterator.startSymbolid < numOfSyms; iterator.startSymbolid++)
                {
                    // Send U-Plane message;                    

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

std::cout << "\nDATADIR: " << iterator.dataDirection;
std::cout << "\nPAYLOADVER: " << iterator.payloadVersion;
std::cout << "\nFILTERINDEX: " << iterator.filterIndex;
std::cout << "\nFRAMEID: " << iterator.frameId;
std::cout << "\nSUBFRAMEID: " << iterator.subframeId;
std::cout << "\nSLOTID: " << iterator.slotId;
std::cout << "\nSTARTSYMBID: " << iterator.startSymbolid;

std::cout << "\nNUMOFSECTIONS: " << iterator.numberOfsections;
std::cout << "\nSECTIONTYPE: " << iterator.sectionType;

std::cout << "\nudcomphdr: " << iterator.udCompHdr;
std::cout << "\nreserved: " << iterator.reserved;
std::cout << "\nrb: " << iterator.rb;
std::cout << "\nsyminc: " << iterator.symInc;
std::cout << "\nstartprbc: " << iterator.startPrbc;


    std::cout << "\nNUMOFPRB: " << iterator.numPrbc;

std::cout << "\nremask: " << iterator.reMask;
std::cout << "\nnumsymbol: " << iterator.numSymbol;
std::cout << "\nef: " << iterator.ef;
std::cout << "\nbeamid: " << iterator.beamId << "\n\n";


std::string test;
//std::cin >> test;


                    runResult = process->run(iterator, data);
                    if (runResult == RETURN_FAILURE) // Failed
                    {
                        std::cout << "run failed\n";
                        return (RETURN_FAILURE);
                    }
                    else if (runResult == RETURN_TIMEDOUT) // Timed out
                    {
                        return (RETURN_TIMEDOUT);
                    }




                    useTransfer->sendForPack(data, iterator, CPstruct, UPstruct);
                    // Pack after display output so data isn't skewed, this will be removed later
                }
            }
        }
    }
    return (0);
}

/*
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
*/