
// --------------------------------------

#include "sender.hpp"
#include "receiver.hpp"
#include "transfer.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

    Transfer *process = nullptr;
    std::clock_t start;
    double duration;
    int run;

    if (argc == 2)
    {
        // Convert argv[1] to a string by copying it
        std::string inputType(argv[1]);

        if (inputType == "sender")
        {
            process = new Sender();

            for(int i = 0; i < 5; i++)
            {

                duration = 0;
                start = std::clock();
                run = 0;

                if ((run = process->run()) == 1)
                {
                    std::cout << "run failed\n";
                    return(1);
                }


                while ((duration < 2) && (run != 1)) // Wait 2 seconds if process not been terminated
                {
                    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
                    // CLOCKS_PER_SEC is number of clock ticks per second (1 000 000 ticks per second)
                    // Take current clock minus clock from start divided by ticks per second
                } 

            }
        }
        else if (inputType == "receiver")
        {
            process = new Receiver();

            while(true)
            {
                if (process->run() == 1)
                {
                    std::cout << "run failed\n";
                    return(1);
                }
            }
        }
        else
        {
            std::cout << "Invalid entry\n";
            return(1);
        }

        delete process; // Destructor
    }

    return(0);
}
