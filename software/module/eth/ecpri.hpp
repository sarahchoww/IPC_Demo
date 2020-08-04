#include <config/struct.hpp>

#include <iostream>

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define DEST_MAC0	0x00
#define DEST_MAC1	0x11
#define DEST_MAC2	0x22
#define DEST_MAC3	0x33
#define DEST_MAC4	0x44
#define DEST_MAC5	0x55

#define DEFAULT_IF	"lo"
#define BUF_SIZ		1024




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
    void getData();
    int setUpEth(uint8_t data[], size_t size);
    

};