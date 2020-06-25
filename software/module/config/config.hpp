#pragma once

#include <config/struct.hpp>
#include <config/du.hpp>

class Config : public DU
{
public:    
    int idValue;
    
    int type(Transfer *&process, char *argv[]);
    // Double pointer, single pointer makes a copy of the data, double is the address
    // Sending in a pointer of a pointer

    void configRU();
    void configDU();
    bool configID();
};