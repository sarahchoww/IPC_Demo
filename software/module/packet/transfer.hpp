#pragma once
#include <config/struct.hpp>
#include <encDec/encode.hpp>
#include <eth/ecpri.hpp>

#include <iostream>
#include <ctime> // localtime and asctime
#include <signal.h> // For ctrl-c
#include <cstring>

#include <linux/if_ether.h> // socket
#include <sys/socket.h> // socket

#define RETURN_FAILURE 1
#define RETURN_TIMEDOUT 2



class Transfer
{
protected:
    Encode useEnc;
    Transport useTransport;

public: 

    virtual ~Transfer() = default;

    int setUp(int idValue, uint8_t **data);
    virtual int run(memory_data &iterator, uint8_t data[]) = 0;

    void cleanUpFiles(memory_data &iterator, uint8_t **data);

    void packStruct(uint8_t data[], memory_data &iterator, bitPackCP_t *CPstruct);
    void packStruct(uint8_t data[], memory_data &iterator, bitPackUP_t *UPstruct);


    int passThroughEncode(uint8_t data[], size_t size);
    int passThroughEth(uint8_t data[], size_t size, int msg_type);


};
