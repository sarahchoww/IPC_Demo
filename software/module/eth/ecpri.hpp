#pragma once
#include <config/struct.hpp>

#include <iostream>

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#include <linux/ip.h>
#include <linux/types.h>
#include <asm/byteorder.h>

#define DEST_MAC0	0x11
#define DEST_MAC1	0x22
#define DEST_MAC2	0x33
#define DEST_MAC3	0x44
#define DEST_MAC4	0x55
#define DEST_MAC5	0x66

#define DEFAULT_IF	"lo"
#define BUF_SIZ		1024


#pragma pack(push, 1)
struct ecpri_header
{


    __u8	proto_rev: 4,
        reserved: 3,
        concatenate: 1;


    __u8 message_type; // unsigned char 8 bits
    __be16 payload_size; // be16 - big endian 16 bits, bitwise attributes

};
#pragma pack(pop)


class Transport
{
protected:
    struct transConfig
    {
        unsigned int ecpriVersion;
        unsigned int ecpriReserved;
        bool ecpriConcatenation;
        unsigned int ecpriMessage;
        unsigned int ecpriPayload;
        unsigned int ecpriRtcidPcid;
        unsigned int ecpriSeqid;
    };




public:
    bitPackTrans_t *sendTrans;
    int setUpEth(uint8_t data[]);
    int sendEth(uint8_t data[], size_t size);


};