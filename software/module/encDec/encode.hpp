#include <iostream>
#include <stdint.h>
#include <semaphore.h>

class Encode
{
public:
    void encodeData(uint8_t data[], size_t sizeData, size_t sizeBitPack);

};