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

#define DEST_MAC0	0x11
#define DEST_MAC1	0x22
#define DEST_MAC2	0x33
#define DEST_MAC3	0x44
#define DEST_MAC4	0x55
#define DEST_MAC5	0x66

#define DEFAULT_IF	"lo"
#define BUF_SIZ		1024



struct ecpri_header
{

    #if defined(__LITTLE_ENDIAN_BITFIELD)
    __u8	ihl:4,
        version:4;
    #elif defined (__BIG_ENDIAN_BITFIELD)
    __u8	version:4,
        ihl:4;
    #else
    #error	"Please fix <asm/byteorder.h>"
    #endif
    __u8	tos; // Type of service
    __be16	tot_len; // Total length
    __be16	id;
    __be16	frag_off; // Fragmentation
    __u8	ttl; // Time to live - 64?
    __u8	protocol; // 17?
    __sum16	check; // Checking - optional?
    __be32	saddr; // Source address
    __be32	daddr; // Destination address
    /*The options start here. */

};


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
    void getData(size_t totalSize);
    int setUpEth(uint8_t data[]);
    int sendEth(uint8_t data[], size_t size);


};