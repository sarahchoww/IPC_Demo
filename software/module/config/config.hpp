#include <packet/transfer.hpp>

class Config
{
public:
    int type(Transfer **process, char *argv[]); 
    // Double pointer, single pointer makes a copy of the data, double is the address
    // Sending in a pointer of a pointer

    void configRU();
    void configDU();
};