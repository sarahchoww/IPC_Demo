#include <config/config.hpp>

#include <iostream>
#include <cstring>

class DU;

#include <config/du.hpp>

int Config::type(Transfer *&process, char *argv[]) // Change reference to a pointer
{

    setToZero();

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

        //std::cout << "data before\t" << &data << "\tvalue\t" << data << std::endl;
        printf("BEFORE: Address: %p\tValue:  %p\n", &data, data );
        
        process = new Sender(idValue, &data);

        //std::cout << "data after\t" << &data << "\tvalue\t" << data << std::endl;
        printf("AFTER: Address: %p\tValue:  %p\n", &data, data );


        bitPackCP_t *CPstruct = (struct bitPackCP *) data;
        bitPackUP_t *UPstruct = (struct bitPackUP *) data; // Access UP data but point to data

        //std::cout << "\npoointer 1\t" << CPstruct << "\npointer 2\t" << UPstruct << "\npointer 3\t" << data << std::endl;
        printf("pointer1: %p\t pointer2:  %p\t pointer 3: %p\n", CPstruct, UPstruct, data );



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
            result = process->run(iterator, data);

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

void Config::setToZero()
{
    iterator.dataDirection = 0;
    iterator.payloadVersion = 0;
    iterator.filterIndex = 0;
    iterator.frameId = 0;
    iterator.subframeId = 0;
    iterator.slotId = 0;
    iterator.startSymbolid = 0;
    iterator.numberOfsections = 0;
    iterator.sectionType = 0;
    iterator.udCompHdr = 0;
    iterator.reserved = 0;
    iterator.sectionId = 0;
    iterator.rb = 0;
    iterator.symInc = 0;
    iterator.startPrbc = 0;
    iterator.numPrbc = 0;
    iterator.reMask = 0;
    iterator.numSymbol = 0;
    iterator.ef = 0;
    iterator.beamId = 0;
}