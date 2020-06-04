// Sender and receiver program

#include <packet/sender.hpp>
#include <packet/receiver.hpp>
#include <packet/transfer.hpp>

#include <iostream>
#include <string>
#include <libconfig.h++>



int main(int argc, char *argv[])
{
    Transfer *process = nullptr;

    if (argc == 2)
    {
       
    }
    else
    {
        std::cout << "Invalid argument(s)\n";
        return (1);
    }

    /*
    if (process->run() == 1)
    {
        std::cout << "run failed\n";
        return (1);
    }
*/

    delete process; // Destructor
    return (0);
}
