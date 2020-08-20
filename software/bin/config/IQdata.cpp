#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>


int main()
{

    int fileDir, num;
    uint8_t buf[32];

    for (int i = 0; i < 32; i++)
    {
        
        num = rand() % 100;  

        buf[i] = 0b00110000;

        if ((num % 5) == 0) // Space
        {
            buf[i] = 0b00100000;
        }

        if (i % 5 == 0) // New line every 4th
        {
            buf[i] = 0b00001010;
        }
    }




    if ((fileDir = shm_open("/dummyIQ", O_CREAT | O_RDWR, 0600)) == -1) // Open and create a file if it does not already exist
    {
        std::cout << "file opening error\n";
        return (1);
    }

    if (write(fileDir, buf, sizeof(buf)) == -1)
    {
        std::cout << "write failure";
        return(1);
    }

    return(0);




}