#pragma once

struct memory_data
{
    int id;

    int dataDirection;
    unsigned int payloadVersion;
    unsigned int filterIndex;
    unsigned int frameId;
    unsigned int subframeId;
    unsigned int slotId;
    unsigned int startSymbolid;
    unsigned int numberOfsections;
    unsigned int sectionType;
    unsigned int udCompHdr;
    unsigned int sectionId;
    int rb;
    int symInc;
    unsigned int startPrbc;
    unsigned int numPrbc;
    unsigned int reMask;
    unsigned int numSymbol;
    int ef;
    unsigned int beamId;    
    int reserved;

};

