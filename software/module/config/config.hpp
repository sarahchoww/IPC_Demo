#pragma once
#include <iostream>
#include <libconfig.h++>
#include <bitset>

#include <packet/receiver.hpp>
#include <packet/sender.hpp>
//#include <packet/transfer.hpp>
#include <config/struct.hpp>

#define RETURN_FAILURE 1
#define RETURN_TIMEDOUT 2

class Config
{
protected:
    struct configVars
    {
        int bandSectorId;
        int CCid;
        int DUPortId;
        std::string RATtype;        // LTE or NR
        int numerology;          // 15 kHz for LTE
        std::string divisionDuplex; // FDD or TDD
        float bandwidth;           // 1.4, 3, 5, 10, 15, 20 MHz
        std::string prefixType;     // Normal or extended

    };

    bitPackCP_t *sendBit;
    bitPackCP_t sendBitNorm;

    configVars cVar;
    memory_data iterator;
    libconfig::Config cfg;


public:
    int idValue;


    int *data;

    int type(Transfer *&process, char *argv[]);
    // Double pointer, single pointer makes a copy of the data, double is the address
    // Sending in a pointer of a pointer 

    virtual ~Config() = default;
    bool configID();
    int configDU();


    template <class T>
    void accessFile(libconfig::Config &cfg, std::string paramName, T &paramVal)
    {
        try
        {

            T temp = cfg.lookup(paramName);
            paramVal = temp;
            
            std::cout << "From config file " << paramName << ": " << paramVal << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << "\tlookUp\n";
        }
    }


    std::string accessFileStr(libconfig::Config &cfg, std::string paramName);
    unsigned int accessFileUnSignedInt(libconfig::Config &cfg, std::string paramName);
    float accessFileFloat(libconfig::Config &cfg, std::string paramName);
    int accessFileInt(libconfig::Config &cfg, std::string paramName);


    virtual void DUsetUp(configVars &cVar, memory_data &iterator){};
    virtual int rotateGrid(memory_data &iterator, Transfer *&process, int *data, bitPackCP_t *CPstruct, bitPackUP_t *UPstruct) {return 1;};

};