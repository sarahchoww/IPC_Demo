#include <config/config.hpp>

#include <iostream>
#include <cstring>

class DU;

#include <config/du.hpp>

int Config::type(Transfer *&process, char *argv[]) // Change reference to a pointer
{
    // Convert argv[1] to a string by copying it
    std::string inputType1(argv[1]);
    bool idFail;
    configVars cVar;
    memory_data iterator;



    // Get ID
    if ((idFail = configID(iterator)) == true)
    {
        std::cout << "ID error\n";
        return (1);
    }


    if (inputType1 == "sender")
    {
        process = new Sender(idValue, sendBit);
        if (configDU(cVar) == 1)
        {
            std::cout << "configDU failed\n";
            return(1);
        }
        Config *useDU = new DU(cVar, iterator, sendBit);
        useDU->rotateGrid(iterator, process, sendBit);

    }
    else if (inputType1 == "receiver")
    {
        process = new Receiver(idValue, sendBit);
        
        if (process->run(iterator, sendBit) == 1)
        {
            std::cout << "run failed\n";
            return (1);
        }

    }
    else
    {
        std::cout << "Invalid entry\n";
        return (1);
    }

    return (0);
}

int Config::configDU(configVars &cVar)
{
    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin");

    try
    {
        cfg.readFile("config/configDU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\t readFile\n";
        return (1);
    }


    sendBit->dataDirection = accessFileInt(cfg, "dataDirection");
    sendBit->payloadVersion = accessFileUnSignedInt(cfg, "payloadVersion");

    cVar.bandSectorId = accessFileInt(cfg, "bandSectorId");
    cVar.CCid = accessFileInt(cfg, "CCid");
    cVar.DUPortId = accessFileInt(cfg, "DUPortId");
    cVar.RATtype = accessFileStr(cfg, "RATtype");
    cVar.numerology = accessFileInt(cfg, "numerology");
    cVar.divisionDuplex = accessFileStr(cfg, "divisionDuplex");
    cVar.bandwidth = accessFileInt(cfg, "bandwidth");
    cVar.prefixType = accessFileStr(cfg, "prefixType");


    return(0);
}

bool Config::configID(memory_data &iterator)
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
        std::cout << "From config file ID: " << idValue << std::endl;
        iterator.id = idValue;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }

    return false;
}

std::string Config::accessFileStr(libconfig::Config &cfg, std::string paramName)
{
    try
    {
        std::string passStr = cfg.lookup(paramName);
        std::cout << "From config file " << paramName << ": " << passStr << std::endl;
        return passStr;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\tlookUp\n";
    }
    return NULL;
}

unsigned int Config::accessFileUnSignedInt(libconfig::Config &cfg, std::string paramName)
{
    unsigned int num;
    try
    {
        num = cfg.lookup(paramName);
        std::cout << "From config file " << paramName << ": " << num << std::endl;
        return num;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\tlookUp\n";
    }
    return num;
}


int Config::accessFileInt(libconfig::Config &cfg, std::string paramName)
{
    int num;
    try
    {
        num = cfg.lookup(paramName);
        std::cout << "From config file " << paramName << ": " << num << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\tlookUp\n";
    }
    return num;
}