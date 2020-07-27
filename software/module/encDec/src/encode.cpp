#include <encDec/encode.hpp>

/*
New train of thought:

Send over all of the bits for CPstruct / UPstruct
EncodeData: 
    Group the number of bits to swap into groups of 4
    Swap those
    Move onto next group of 4
    Swap those
    Repeat until reach the end

*/



// plane determines which plane to take data from: 0 = UP, 1 = CP
void Encode::encodeData(int **data, size_t size) // Possible to locate a single byte, byteNum
{
    int num;
    /*
    for (size_t newSize = 0; newSize < size; newSize += 8)
    {        
        num = **data;
        //std::cout << "value\t" << std::dec << data[newSize] << std::endl;

        std::bitset<8> x(num);
        std::cout << "before\t" << x << std::endl;

        num = (num >> 4) | (num << 4);
        num = ((num & 0xCC) >> 2) | ((num & 0x33) << 2);
        num = ((num & 0xAA) >> 1) | ((num & 0x55) << 1);

        **data = num;
        std::cout << "after\t" << x << std::endl;

        std::cout << std::endl;

        
    }
    */

}
