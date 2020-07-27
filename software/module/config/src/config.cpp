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
    sendBit = &sendBitNorm; // To properly access the struct members


    libconfig::Config cfg;
    cfg.setIncludeDir("software/bin");

    int result; // For the status of receiver

    // Get ID
    if ((idFail = configID()) == true)
    {
        std::cout << "ID error\n";
        return (RETURN_FAILURE);
    }


    if (inputType1 == "sender")
    {

        std::cout << "data before\t" << data << std::endl;
        
        process = new Sender(idValue, &data);

        std::cout << "data after\t" << data << std::endl;

/*
       uint8_t *val;

	uint8_t **ptr1 = &val;


	std::cout << "\nval\t" << val << "\nptr1\t" << *ptr1 << std::endl;
 */


    bitPackCP_t *CPstruct = (struct bitPackCP *) data;
    bitPackUP_t *UPstruct = (struct bitPackUP *) data; // Access UP data but point to data

    std::cout << "\nnew\npoointer 1\t" << CPstruct << "\npointer 2\t" << UPstruct << "\npointer 3\t" << data << std::endl;

    std::string test;
    //std::cin >> test;

        if (configDU() == RETURN_FAILURE)
        {
            std::cout << "configDU failed\n";
            return(RETURN_FAILURE);
        }
        Config *useDU = new DU();
        useDU->DUsetUp(cVar, iterator);

        if ((useDU->rotateGrid(iterator, process, data, CPstruct, UPstruct)) == RETURN_TIMEDOUT)
        {
            delete useDU;
            return(0);
        }
        


        delete useDU;

    }
    else if (inputType1 == "receiver")
    {
        process = new Receiver(idValue, &data);

        while (true)
        {
            result = process->run(iterator, &data);

            if (result == RETURN_FAILURE)
            {
                std::cout << "run failed\n";
                return(RETURN_FAILURE);
            }
            else if (result == RETURN_TIMEDOUT)
            {
                // Not a failure, but exit out of loop
                
                return (0);
            }
            
        }
    }
    else
    {
        std::cout << "Invalid entry\n";
        return (RETURN_TIMEDOUT);
    }

    delete sendBit;
    return (0);
}

int Config::configDU()
{
    try
    {
        cfg.readFile("config/configDU.cfg");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\t readFile\n";
        return (RETURN_FAILURE);
    }


    accessFile(cfg, "dataDirection", iterator.dataDirection);
    accessFile(cfg, "payloadVersion", iterator.payloadVersion);

    accessFile(cfg, "bandSectorId", cVar.bandSectorId);
    accessFile(cfg, "CCid", cVar.CCid);
    accessFile(cfg, "DUPortId", cVar.DUPortId);
    accessFile(cfg, "RATtype", cVar.RATtype);
    accessFile(cfg, "numerology", cVar.numerology);
    accessFile(cfg, "divisionDuplex", cVar.divisionDuplex);
    accessFile(cfg, "bandwidth", cVar.bandwidth);
    accessFile(cfg, "prefixType", cVar.prefixType);

    return(0);
}

bool Config::configID()
{
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