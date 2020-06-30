// Sender and receiver program

#include <packet/transfer.hpp>
#include <config/config.hpp>

#include <iostream>
#include <string>
#include <libconfig.h++>


int main(int argc, char *argv[])
{
    Transfer *process = nullptr;
    Config setUpProcess;

    if (argc == 2)
    {
       if ((setUpProcess.type(process, argv)) == 1) // Send process
       {
           return(1);
       }
    }
    else
    {
        std::cout << "Invalid argument(s)\n";
        return (1);
    }


    delete process; // Destructor
    return (0);
}
