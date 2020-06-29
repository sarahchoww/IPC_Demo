#pragma once

struct memory_data
{
    //int id;

    //int dataDirection;
    //unsigned int payloadVersion;
    unsigned int filterIndex;
    unsigned int frameId;
    unsigned int subframeId;
    unsigned int slotId;
    unsigned int startSymbolid;
    unsigned int numberOfsections;
    unsigned int sectionType;
    unsigned int udCompHdr;
    int reserved;
    unsigned int sectionId;
    int rb;
    int symInc;
    unsigned int startPrbc;
    unsigned int numPrbc;
    unsigned int reMask;
    unsigned int numSymbol;
    int ef;
    unsigned int beamId;    

};


typedef struct bitPack
{
    int id;

    int dataDirection : 1;
    unsigned int payloadVersion : 3;
    unsigned int filterIndex : 4;
    unsigned int frameId : 8;
    unsigned int subframeId : 4;
    unsigned int slotId : 6;
    unsigned int startSymbolid : 6;
    unsigned int numberOfsections : 8;
    unsigned int sectionType : 8;
    unsigned int udCompHdr : 8;
    int reserved : 8;
    unsigned int sectionId : 12;
    int rb : 1;
    int symInc : 1;
    unsigned int startPrbc : 10;
    unsigned int numPrbc : 8;
    unsigned int reMask : 12;
    unsigned int numSymbol : 4;
    int ef : 1;
    unsigned int beamId : 15;    
} bitPack_t;



