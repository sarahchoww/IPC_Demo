#include <encDec/encode.hpp>

void Encode::encodeData(uint8_t data[], size_t sizeData)
{
    uint8_t x;

    for (size_t newSize = 0; newSize < sizeData; newSize++)
    {   
        x = data[newSize];   
        
        printf("value1: %d\n", data[newSize]);

        x = (x >> 4) | (x << 4);
        x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
        x = ((x & 0xAA) >> 1) | ((x & 0x55) << 1);	

        data[newSize] = x;

        printf("value2: %d\n", data[newSize]);
        std::cout << std::endl;
    }
    
}