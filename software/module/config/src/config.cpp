
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
    std::string semNewDataFile, semReceivedFile, fileId;


    if (inputType1 == "sender")
    {
        semNewDataFile, semReceivedFile, fileId = configRU();
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

std::string Config::configRU()
{
    int RUid;
    std::string semNewDataFile, semReceivedFile, fileId;

    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin/config");

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

    RUid = getpid();

    semNewDataFile = SEM_NEWDATA + std::to_string(RUid);
    semReceivedFile = SEM_RECEIVED + std::to_string(RUid);
    fileId = FILENAME + std::to_string(RUid);

    return semNewDataFile, semReceivedFile, fileId;

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