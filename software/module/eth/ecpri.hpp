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

#include <unistd.h>


#define DEST_MAC0	0xa4
#define DEST_MAC1	0xbb
#define DEST_MAC2	0x6d
#define DEST_MAC3	0x47
#define DEST_MAC4	0xe8
#define DEST_MAC5	0x0c

#define SENDER_IF	"lo"
#define RECEIVER_IF "enp1s0"
#define ETHER_TYPE 0xaefe /* ECPRI */

#define BUF_SIZ		1024


#pragma pack(push, 1)
struct ecpri_header
{


    __u8    concatenate: 1,
        reserved: 3,
        proto_rev: 4;

    __u8 message_type; // unsigned char 8 bits
    __be16 payload_size; // be16 - big endian 16 bits, bitwise attributes
    __be16 rtcid_pcid; // Real time control data / IQ data transfer message series identifier
    __be16 seqid; // Sequence ID

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