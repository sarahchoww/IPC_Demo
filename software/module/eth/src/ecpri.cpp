#include <eth/ecpri.hpp>

int Transport::sendEth(uint8_t data[], size_t sizeStruct)
{
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
	if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) < 0)
	{
		perror("socket()");
		return (1);
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ - 1);

	// Interface index
	if (ioctl(socketFileDir, SIOCGIFINDEX, &ifr) < 0)
	{
		perror("SIOCGIFINDEX");
		close(socketFileDir);
	}
	if_index = ifr.ifr_ifindex;


	// Interface address
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


	// Fill out ecpri header
	ecpri->proto_rev = 1;
	ecpri->reserved = 0;
	ecpri->concatenate = 0;
	ecpri->message_type = 0; // IQ data type
	ecpri->payload_size = htons(sizeStruct + 4); // Add 4 bytes to account / offset for RTCID and SeqId in payload
	ecpri->rtcid_pcid = htons(1);
	ecpri->seqid = htons(1);
	


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
