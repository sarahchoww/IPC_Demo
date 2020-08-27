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
            iterator.numSymbol = 7;
        }
        else // Extended
        {
            iterator.numSymbol = 6;
        }

        // number of PRBs
        if (cVar.bandwidth == 1.4)
        {
            iterator.numPrbc = 6; // Can change
            iterator.numPrbu = 6; // Can change
        }
        else
        {
            iterator.numPrbc = cVar.bandwidth * 5;
            iterator.numPrbu = cVar.bandwidth * 5;
        }
    }
    else // NR
    {
        std::cout << "RATtype:\t" << cVar.RATtype << std::endl;
    }
}

int DU::rotateGrid(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackCP_t *CPstruct, bitPackUP_t *UPstruct)
{
    for (iterator.frameId = 0; (int)iterator.frameId < numOfFrames; iterator.frameId++)
    {
        for (iterator.subframeId = 0; (int)iterator.subframeId < numOfSubframes; iterator.subframeId++)
        {

            for (iterator.slotId = 0; (int)iterator.slotId < numOfSlots; iterator.slotId++)
            {

                for (iterator.startPrbc = 0; iterator.startPrbc < iterator.numPrbc; iterator.startPrbc++)
                {

                    for (iterator.startSymbolid = 0; iterator.startSymbolid < iterator.numSymbol; iterator.startSymbolid++) // Won't always start at 0
                    {

                        // can have multiple U-Plane messages per C-Plane message

                        std::cout << "sending CP\n";
                        sendData(iterator, process, data, CPstruct);

                        for (iterator.startPrbu = 0; iterator.startPrbu < iterator.numPrbu; iterator.startPrbu++) // UP PRB
                        {
                            for (iterator.symbolId = 0; iterator.symbolId < 12; iterator.symbolId++) // UP Symbols
                            {
                                std::cout << "sending UP\n";


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
                                std::cout << "\nbeamid: " << iterator.beamId;

                                std::cout << "\n\t\tUPLANE:";
                                std::cout << "\n SYMBOLID: " << iterator.symbolId;
                                std::cout << "\n STARTPRBU: " << iterator.startPrbu;
                                std::cout << "\n NUMPRBU: " << iterator.numPrbu << "\n\n";

                                sendData(iterator, process, data, UPstruct);
                            }
                        }
                    }
                }
            }
        }
    }
    return (0);
}

// C-Plane
int DU::sendData(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackCP_t *planeStruct)
{
    int runResult;

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

    useTransfer->packStruct(data, iterator, planeStruct);

    if ((useTransfer->passThroughEncode(data, sizeof(bitPackCP_t))) == RETURN_FAILURE)
    {
        return (RETURN_FAILURE);
    }

    if ((useTransfer->passThroughEth(data, sizeof(bitPackCP_t))) == RETURN_FAILURE)
    {
        return (RETURN_FAILURE);
    }

    return (0);
}

// U-Plane
int DU::sendData(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackUP_t *planeStruct)
{
    int runResult;

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

    useTransfer->packStruct(data, iterator, planeStruct);

    if ((useTransfer->passThroughEncode(data, sizeof(bitPackUP_t))) == RETURN_FAILURE)
    {
        return (RETURN_FAILURE);
    }

    if ((useTransfer->passThroughEth(data, sizeof(bitPackUP_t))) == RETURN_FAILURE)
    {
        return (RETURN_FAILURE);
    }

    return (0);
}