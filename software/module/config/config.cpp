#include <config/config.hpp>
#include <packet/receiver.hpp>
#include <packet/sender.hpp>
#include <packet/transfer.hpp>

#include <iostream>
#include <libconfig.h++>

int Config::inputType(Transfer *process)
{
     // Convert argv[1] to a string by copying it
        std::string inputType(argv[1]);

        if (inputType == "sender")
        {
            configRU();
            process = new Sender();
        }
        else if (inputType == "receiver")
        {
            configDU();
            process = new Receiver();
        }
        else
        {
            std::cout << "Invalid entry\n";
            return (1);
        }
        return(0);
}


void Config::configRU()
{
    libconfig::Config cfg;
    cfg.setIncludeDir("software/module");

    try
    {
        cfg.readFile("relocateRU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Name
    try
    {
        std::string name = cfg.lookup("name");
        std::cout << name << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}




void Config::configDU()
{
    libconfig::Config cfg;
    //cfg.setIncludeDir("software/module");

    try
    {
        cfg.readFile("relocateDU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }


    // Name
    try
    {
        std::string name = cfg.lookup("name");
        std::cout << name << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}