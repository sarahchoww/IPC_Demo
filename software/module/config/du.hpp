#include <config/config.hpp>
#include <config/struct.hpp>

class DU : public Config
{
protected:

    struct iqDataStruct
    {
        float i;
        float q;

    }typedef iqDataStruct_t;


    int numOfFrames;
    int numOfSubframes;
    int numOfSlots;
    int numOfSyms;

    Transfer *useTransfer;
    //iqDataStruct_t iqArr[20];

    signed int iData;
    signed int qData;

public:
    void DUsetUp(configVars &cVar, memory_data &iterator);
    int rotateGrid(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackCP_t *CPstruct, bitPackUP_t *UPstruct);
    int sendData(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackCP_t *planeStruct);
    int sendData(memory_data &iterator, Transfer *&process, uint8_t data[], bitPackUP_t *planeStruct);
    void genIQData();

};