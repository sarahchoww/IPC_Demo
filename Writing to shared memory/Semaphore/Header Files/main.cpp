
// --------------------------------------

#include "sender.hpp"
#include "receiver.hpp"
#include "transfer.hpp"

#include <iostream>
#include <string>



int main(int argc, char *argv[])
{

    Transfer *process;

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

    if (process->setUp() == 1)
    {
        std::cout << "Setup failed\n"; 
    }
    else
    {
        for(int i = 0; i < 1; i++)
        {
            if (process->run() == 1)
            {
                std::cout << "Run failed\n"
                        << std::endl;
            }
        }
    }



    process->cleanUp();



    return (0);
}
