// Sender and receiver program

#include <packet/transfer.hpp>
#include <config/config.hpp>

#include <iostream>
#include <string>
#include <libconfig.h++>



int main(int argc, char *argv[])
{
    Transfer *process = nullptr;
    Config *setUpProcess = nullptr;

    if (argc == 2)
    {
       setUpProcess->type(&process, argv); // Send the value of process / 'nullptr' (?)
    }
    else
    {
        std::cout << "Invalid argument(s)\n";
        return (1);
    }


    if (process->run() == 1)
    {
        std::cout << "run failed\n";
        return (1);
    }


    delete process; // Destructor
    return (0);
}
