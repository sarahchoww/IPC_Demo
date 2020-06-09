#pragma once
#include <packet/transfer.hpp>
#include <packet/receiver.hpp>
#include <packet/sender.hpp>

class Config
{
protected:
    // dataDirection binary bit
    // rb binary bit
    // symInc binary bit
    // ef binary bit
    // sfStatus binary bit
    // lbtDrsRes binary bit
    // initialPartialSF binary bit
    // lbtBufErr binary bit
    // lbtCWR_Rst binary bit

    // reserved variable

    unsigned int payloadVersion, filterIndex, frameId, subframeId, slotId, startSymbolid, numberOfsections, sectionType, numberOfUEs, timeOffset, cpLength, sectionId, startPrbc, reMask, numPrbc, numSymbol, beamId, ueId, regularizationFactor, laaMsgType, laaMsgLen,
    lbtHandle, lbtDeferFactor, lbtBackoffCounter, lbtOffset, MCOT, lbtMode, lbtPdschRes, sfnSf, lbtCWConfig_H, lbtCWConfig_T,
    lbtTrafficClass;
    signed int freqOffset, ciIsample, ciQsample;
    unsigned int frameStructure; // concatenated bit fields



public : 
    int id;
    int type(Transfer *&process, char *argv[]);
    // Double pointer, single pointer makes a copy of the data, double is the address
    // Sending in a pointer of a pointer

    void configRU();
    void configDU();
    bool configID();
};