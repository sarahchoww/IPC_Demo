#include <config/config.hpp>
#include <config/struct.hpp>

class DU : public Config
{
protected:

/*
    enum LTE
    {
        numOfFrames = 256, // Follow up
        numOfSubframes = 10,
        numOfSlots = 2,
        numOfSyms = 7, // Standard for 7 symbols, can't change *************8
        numPrbc = 15   // num of PRB, change?
    };

*/

    int numOfFrames;
    int numOfSubframes;
    int numOfSlots;
    int numOfSyms;

    Transfer *useTransfer;

public:
    void DUsetUp(configVars &cVar, memory_data &iterator);
    int rotateGrid(memory_data &iterator, Transfer *&process, int *data, bitPackCP_t *CPstruct, bitPackUP_t *UPstruct);

};