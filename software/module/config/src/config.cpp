#include <config/config.hpp>

#include <iostream>
#include <libconfig.h++>
#include <cstring>

int Config::type(Transfer *&process, char *argv[]) // Change reference to a pointer
{

    // Convert argv[1] to a string by copying it
    std::string inputType1(argv[1]);
    bool idFail;
    
    // Get ID
    if ((idFail = configID()) == true)
    {
        std::cout << "ID error\n";
        return(1);
    }


    configDU();

    if (inputType1 == "sender")
    {
        setData();
        process = new Sender(idValue);

    }
    else if (inputType1 == "receiver")
    {
        process = new Receiver(idValue);

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
        std::cout << "From config file NAME: " << name << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        iterator.dataDirection = cfg.lookup("dataDirection");
        std::cout << "From config file DATADIRECTION: " << iterator.dataDirection << std::endl;
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
        std::cout << "From config file NAME: " << name << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // dataDirection
    try
    {
        iterator.dataDirection = cfg.lookup("dataDirection");
        std::cout << "From config file DATADIRECTION: " << iterator.dataDirection << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // payloadVersion
    try
    {
        iterator.payloadVersion = cfg.lookup("payloadVersion");
        std::cout << "From config file PAYLOADVERSION: " << iterator.payloadVersion << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

}

// Add a part to change ID if user enters a specific argv?
bool Config::configID()
{
    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin");

    try
    {
        cfg.readFile("config/configID.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }

    // Name
    try
    {
        idValue = cfg.lookup("id");
                std::cout << "hello there\n";

        std::cout << "From config file ID: " << idValue << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }
        std::cout << "hello\n";


    return false;
}