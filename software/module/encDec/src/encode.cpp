#include <encDec/encode.hpp>

void Encode::encodeData(uint8_t data[], size_t sizeData)
{
    uint8_t x;

    for (size_t newSize = 0; newSize < sizeData; newSize++)
    {   
        x = data[newSize];   


        x = (x >> 4) | (x << 4);
        x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
        x = ((x & 0xAA) >> 1) | ((x & 0x55) << 1);	

        data[newSize] = x;


        std::string binary2 = std::bitset<8>(data[newSize]).to_string(); //to binary
        std::cout << binary2 <<" ";

    }

    std::cout << "\n\n";
    
}