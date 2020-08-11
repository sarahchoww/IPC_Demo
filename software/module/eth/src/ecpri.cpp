#include <eth/ecpri.hpp>

void Transport::getData(size_t totalSize)
{
    sendTrans->ecpriVersion = 1; // Version 1
    sendTrans->ecpriMessage = 0; // IQ data type
    sendTrans->ecpriConcatenation = 0; // No concatenation
    sendTrans->ecpriPayload = totalSize; // Size of payload


}


int Transport::sendEth(uint8_t data[], size_t sizeStruct)
{

    int socketFileDir;
	struct ifreq interfaceIndex; // Interface index
	struct ifreq MACInterface; // MAC interface


	char interfaceName[IFNAMSIZ] = DEFAULT_IF;
	struct sockaddr_ll socketAddr;


	struct ether_header *eh = (struct ether_header *) data;
	struct iphdr *ip = (struct iphdr *) (data + sizeof(struct ether_header));

	size_t totalSize = sizeStruct + sizeof(struct ether_header) + sizeof(struct iphdr);


	/* Open RAW socket to send on */
	if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) 
    {
	    std::cout << "socket opening error\n";
		perror("socket");
        return(-1);
	}


	/* Get the index of the interface to send on */
	memset(&interfaceIndex, 0, sizeof(struct ifreq)); // Sets value of interfaceIndex to 0 the size of ifreq

	strncpy(interfaceIndex.ifr_name, interfaceName, IFNAMSIZ-1); 
    // Copies interfaceName to interfaceIndex struct, size of max buffer size minus the terminating 0

    // Manipulates underlying device parameters of special files ????, typically to control the terminal
    // SIOGCGIFINDEX gets the index of the interface into socketFileDir
    if (ioctl(socketFileDir, SIOCGIFINDEX, &interfaceIndex) < 0)
    {
        std::cout << "IOCTL error\n";
        return(-1);
    }


	/* Get the MAC address of the interface to send on */
	memset(&MACInterface, 0, sizeof(struct ifreq));

	strncpy(MACInterface.ifr_name, interfaceName, IFNAMSIZ-1);

    // SIOCGIFHWADDR gets the address of a device using socketFileDir
	if (ioctl(socketFileDir, SIOCGIFHWADDR, &MACInterface) < 0)
	{
        std::cout << "IOCTL error\n";
        return(-1);
    }


  struct sockaddr_in saddr, daddr; // IP source and destination 

  ip->ihl      = 5; //header length, number of 32-bit words 
  ip->version  = 4;
  ip->tos      = 0x0;
  ip->id       = 0;
  ip->frag_off = htons(0x4000); // Don't fragment 
  ip->ttl      = 64;
  ip->tot_len  = htons(sizeof(struct iphdr) + 0);
  ip->protocol = IPPROTO_UDP;
  ip->saddr    = saddr.sin_addr.s_addr;
  ip->daddr    = daddr.sin_addr.s_addr;



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
	eh->ether_type = htons(ETH_P_IP);



	/* Index of the network device */
	socketAddr.sll_ifindex = interfaceIndex.ifr_ifindex;
	/* Address length*/
	socketAddr.sll_halen = ETH_ALEN;
	/* Destination MAC */
	socketAddr.sll_addr[0] = DEST_MAC0;
	socketAddr.sll_addr[1] = DEST_MAC1;
	socketAddr.sll_addr[2] = DEST_MAC2;
	socketAddr.sll_addr[3] = DEST_MAC3;
	socketAddr.sll_addr[4] = DEST_MAC4;
	socketAddr.sll_addr[5] = DEST_MAC5;

	getData(totalSize);

	
	//int result = sendto(socketFileDir, data, size, 0, 0, 0);

    //if (result < 0)
	    //if (sendto(socketFileDir, data, size, 0, (struct sockaddr*)&socketAddr, sizeof(struct sockaddr_ll)) < 0)


	if (sendto(socketFileDir, data, totalSize, 0, (struct sockaddr*)&socketAddr, sizeof(struct sockaddr_ll)) < 0)
    {
        std::cout << "sendto error\n" << std::endl;
        return (1);
    }
	/*
	else
	{
		std::cout << "characters sent\t" << result << std::endl;
	}
	*/

	return(0);
}