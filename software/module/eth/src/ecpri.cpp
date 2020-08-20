#include <eth/ecpri.hpp>

int Transport::sendEth(uint8_t data[], size_t sizeStruct)
{

	/*
    int socketFileDir;

	struct ifreq interfaceIndex; // Interface index
	struct ifreq MACInterface; // MAC interface

	char interfaceName[IFNAMSIZ] = SENDER_IF;
	struct sockaddr_ll socketAddr;


	struct ether_header *eh = (struct ether_header *) data;
	//struct iphdr *ip = (struct iphdr *) (data + sizeof(struct ether_header));

	struct ecpri_header *ecpri = (struct ecpri_header *) (data + sizeof(ether_header));

	size_t totalSize = sizeStruct + sizeof(struct ether_header) + sizeof(struct ecpri_header);



	// Open RAW socket to send on 
	if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) == -1) 
    {
	    std::cout << "socket opening error\n";
		perror("socket");
        return(-1);
	}



	memset(&interfaceIndex, 0, sizeof(struct ifreq)); // Sets value of interfaceIndex to 0 the size of ifreq

	strncpy(interfaceIndex.ifr_name, interfaceName, IFNAMSIZ-1); 
    // Copies interfaceName to interfaceIndex struct, size of max buffer size minus the terminating 0

    // Manipulates underlying device parameters of special files ????, typically to control the terminal
    // SIOGCGIFINDEX gets the index of the interface into socketFileDir



	// Get the MAC address of the interface to send on 
	memset(&MACInterface, 0, sizeof(struct ifreq));
	strncpy(MACInterface.ifr_name, interfaceName, IFNAMSIZ-1);


    if (ioctl(socketFileDir, SIOCGIFINDEX, &interfaceIndex) < 0)
    {
        std::cout << "IOCTL error\n";
        return(-1);
    }

    // SIOCGIFHWADDR gets the address of a device using socketFileDir
	if (ioctl(socketFileDir, SIOCGIFHWADDR, &MACInterface) < 0)
	{
        std::cout << "IOCTL error\n";
        return(-1);
    }



	eh->ether_shost[0] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[0];
	eh->ether_shost[1] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[1];
	eh->ether_shost[2] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[2];
	eh->ether_shost[3] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[3];
	eh->ether_shost[4] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[4];
	eh->ether_shost[5] = ((uint8_t *)&MACInterface.ifr_hwaddr.sa_data)[5];
	eh->ether_dhost[0] = DEST_MAC0;
	eh->ether_dhost[1] = DEST_MAC1;
	eh->ether_dhost[2] = DEST_MAC2;
	eh->ether_dhost[3] = DEST_MAC3;
	eh->ether_dhost[4] = DEST_MAC4;
	eh->ether_dhost[5] = DEST_MAC5;
	// Ethertype field 
	eh->ether_type = htons(0xaefe);


	ecpri->proto_rev = 1;
	ecpri->reserved = 0;
	ecpri->concatenate = 0;
	ecpri->message_type = 0; // IQ data type
	ecpri->payload_size = htons(sizeStruct);
	ecpri->rtcid_pcid = 1;
	ecpri->seqid = 1;
	

	socketAddr.sll_ifindex = interfaceIndex.ifr_ifindex;
	socketAddr.sll_halen = ETH_ALEN;
	socketAddr.sll_addr[0] = DEST_MAC0;
	socketAddr.sll_addr[1] = DEST_MAC1;
	socketAddr.sll_addr[2] = DEST_MAC2;
	socketAddr.sll_addr[3] = DEST_MAC3;
	socketAddr.sll_addr[4] = DEST_MAC4;
	socketAddr.sll_addr[5] = DEST_MAC5;

      fprintf(stdout, "%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x ", eh->ether_shost[0], eh->ether_shost[1], eh->ether_shost[2],
              eh->ether_shost[3], eh->ether_shost[4], eh->ether_shost[5], eh->ether_dhost[0], eh->ether_dhost[1], eh->ether_dhost[2],
              eh->ether_dhost[3], eh->ether_dhost[4], eh->ether_dhost[5]);

	if (sendto(socketFileDir, data, totalSize, 0, (struct sockaddr*)&socketAddr, sizeof(socketAddr)) < 0)
    {
        std::cout << "sendto error\n" << std::endl;
        return (1);
    }


	close(socketFileDir);

*/

	char *interfaceName;
	int socketFileDir;
	int if_index;
	uint8_t if_addr[ETH_ALEN];
	uint8_t dest_addr[ETH_ALEN];
	struct sockaddr_ll sock_addr;


	struct ifreq ifr;



	struct ether_header *eh = (struct ether_header *) data;

	struct ecpri_header *ecpri = (struct ecpri_header *) (data + sizeof(ether_header));

	size_t totalSize = sizeStruct + sizeof(struct ether_header) + sizeof(struct ecpri_header);



	interfaceName = "lo";

	dest_addr[0] = 0xa4;
	dest_addr[1] = 0xbb;
	dest_addr[2] = 0x6d;
	dest_addr[3] = 0x47;
	dest_addr[4] = 0xe8;
	dest_addr[5] = 0x0c;

	/* Create the AF_PACKET socket. */
	if (socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE)) < 0)
	{
		perror("socket()");
		return (1);
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ - 1);

	if (ioctl(socketFileDir, SIOCGIFINDEX, &ifr) < 0)
	{
		perror("SIOCGIFINDEX");
		close(socketFileDir);
	}
	if_index = ifr.ifr_ifindex;

	if (ioctl(socketFileDir, SIOCGIFHWADDR, &ifr) < 0)
	{
		perror("SIOCGIFHWADDR");
		close(socketFileDir);
	}
	memcpy(if_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);



	/* Ethernet header */
	memcpy(eh->ether_shost, if_addr, ETH_ALEN);
	memcpy(eh->ether_dhost, dest_addr, ETH_ALEN);
	eh->ether_type = htons(ETHER_TYPE);



	sock_addr.sll_ifindex = if_index;
	sock_addr.sll_halen = ETH_ALEN;
	memcpy(sock_addr.sll_addr, dest_addr, ETH_ALEN);

	if (sendto(socketFileDir, data, totalSize, 0, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
	{
		perror("sendto()");
		close(socketFileDir);
	}

	close(socketFileDir);

	return (0);
}
