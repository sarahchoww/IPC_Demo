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

#pragma pack(push, 1)
typedef struct bitPackCP
{
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
    unsigned int reserved : 8;
    unsigned int sectionId : 12;
    int rb : 1;
    int symInc : 1;
    unsigned int startPrbc : 10;
    unsigned int numPrbc : 8;
    unsigned int reMask : 12;
    unsigned int numSymbol : 4;
    int ef : 1;
    unsigned int beamId : 15;    
} bitPackCP_t;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct bitPackUP
{
    int dataDirection : 1;
    unsigned int payloadVersion : 3;
    unsigned int filterIndex : 4;
    unsigned int frameId : 8;
    unsigned int subframeId : 4;
    unsigned int slotId : 6;
    unsigned int symbolId : 6; // Different
    unsigned int sectionId : 12;
    int rb : 1;
    int symInc : 1;
    unsigned int startPrbu : 10;
    unsigned int numPrbu : 8;
    unsigned int udCompHdr : 8;
    unsigned int reserved : 8;

//own function, gather all samples and then pack
    //unsigned int udCompParam; size varies!
    signed int iSample : 16; // size varies, array
    signed int qSample : 16; // size varies, array
} bitPackUP_t;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct bitPackTrans
{
    unsigned int ecpriVersion : 4;
    unsigned int ecpriReserved : 3;
    int ecpriConcatenation : 1;
    unsigned int ecpriMessage : 8;
    unsigned int ecpriPayload : 16;
    unsigned int ecpriRtcidPcid : 16;
    unsigned int ecpriSeqid : 16;
} bitPackTrans_t;
#pragma pack(pop)