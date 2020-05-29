// Sender and receiver program

#include "sender.hpp"
#include "receiver.hpp"
#include "transfer.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    Transfer *process = nullptr;

    if (argc == 2)
    {
        // Convert argv[1] to a string by copying it
        std::string inputType(argv[1]);

        if (inputType == "sender")
        {
            process = new Sender();
        }
        else if (inputType == "receiver")
        {
            process = new Receiver();
        }
        else
        {
            std::cout << "Invalid entry\n";
            return (1);
        }
    }
    else
    {
        std::cout << "Invalid argument(s)\n";
        return(1);
    }
    

    if (process->run() == 1)
    {
        std::cout << "run failed\n";
        return (1);
    }

    delete process; // Destructor
    return (0);
}
