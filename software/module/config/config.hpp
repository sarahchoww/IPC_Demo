#pragma once
#include <packet/receiver.hpp>
#include <packet/sender.hpp>
#include <config/struct.hpp>
#include <libconfig.h++>

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
        int bandwidth;           // 1.4, 3, 5, 10, 15, 20 MHz
        std::string prefixType;     // Normal or extended

    };

    bitPack_t *sendBit;


public:
    int idValue;

    int type(Transfer *&process, char *argv[]);
    // Double pointer, single pointer makes a copy of the data, double is the address
    // Sending in a pointer of a pointer

    bool configID(memory_data &iterator);
    int configDU(configVars &cVar);

    std::string accessFileStr(libconfig::Config &cfg, std::string paramName);
    unsigned int accessFileUnSignedInt(libconfig::Config &cfg, std::string paramName);

    int accessFileInt(libconfig::Config &cfg, std::string paramName);

    virtual int rotateGrid(memory_data &iterator, Transfer *&process, bitPack_t *&sendBit) {return 1;};

};