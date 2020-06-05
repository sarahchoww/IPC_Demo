#include <config/config.hpp>
#include <packet/receiver.hpp>
#include <packet/sender.hpp>
#include <packet/transfer.hpp>

#include <iostream>
#include <libconfig.h++>
#include <cstring>

int Config::type(Transfer **process, char *argv[])
{
    // Convert argv[1] to a string by copying it
    std::string inputType1(argv[1]);

    if (inputType1 == "sender")
    {
        configRU();
        *process = new Sender(); // Change the address of process
    }
    else if (inputType1 == "receiver")
    {
        configDU();
        *process = new Receiver();
    }
    else
    {
        std::cout << "Invalid entry\n";
        return (1);
    }
    return (0);
}

void Config::configRU()
{
    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin");

    try
    {
        cfg.readFile("config/configRU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Name
    try
    {
        std::string name = cfg.lookup("name");
        std::cout << "From config file: " << name << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Config::configDU()
{
    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin");

    try
    {
        cfg.readFile("config/configDU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Name
    try
    {
        std::string name = cfg.lookup("name");
        std::cout << "From config file: " << name << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}