#include <packet/receiver.hpp>

Receiver::Receiver(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue, data);
    //setUp(data);
}

int Receiver::setUp(uint8_t **data)
{

    if ((*data = (uint8_t *)mmap(NULL, sizeof(bitPackCP_t) + sizeof(bitPackUP_t), PROT_READ | PROT_WRITE, MAP_SHARED, fileDir, 0)) == MAP_FAILED)
    {
        std::cout << "mmap failed\n";
        return (RETURN_FAILURE);
    }

    return (0);
}

int Receiver::run(memory_data &iterator, uint8_t data[])
{

/*
    int socketFileDir;

	struct sockaddr_ll socketAddr;

    char buf[(ETH_FRAME_LEN)];

    struct ifreq ifr;

    char * if_name = RECEIVER_IF;

    uint8_t if_addr[ETH_ALEN];

    int if_index;

    int s;

	struct ifreq MACInterface; // MAC interface



	//struct ether_header *eh = (struct ether_header *) data;                                        
	//struct iphdr *ip = (struct iphdr *) (data + sizeof(struct ether_header));


	if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) == -1) 
    {
	    std::cout << "socket opening error\n";
		perror("socket");
        return(-1);
	}




// NEW

  
	memset(&MACInterface, 0, sizeof(struct ifreq));

	strncpy(MACInterface.ifr_name, DEFAULT_IF, IFNAMSIZ-1);

    // SIOCGIFHWADDR gets the address of a device using socketFileDir
	if (ioctl(socketFileDir, SIOCGIFHWADDR, &MACInterface) < 0)
	{
        std::cout << "IOCTL error\n";
        return(-1);
    }






    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

    if (ioctl(socketFileDir, SIOCGIFFLAGS, &ifr) < 0)
      perror("SIOCGIFFLAGS");

    ifr.ifr_flags |= IFF_PROMISC;

    if (ioctl(socketFileDir, SIOCSIFFLAGS, &ifr) < 0)
      perror("SIOCSIFFLAGS");




    s = 1;
    if (setsockopt(socketFileDir, SOL_SOCKET, SO_REUSEADDR, &s, sizeof(s)) < 0)
    {
      perror("SO_REUSEADDR");
      close(socketFileDir);
      return EXIT_FAILURE;
    }

    if (setsockopt(socketFileDir, SOL_SOCKET, SO_BINDTODEVICE, if_name, IFNAMSIZ - 1) < 0)
    {
      perror("SO_BINDTODEVICE");
      close(socketFileDir);
      return EXIT_FAILURE;
    }

//END





    while (1)
    {


    struct ether_header *eh = (struct ether_header *)buf;
    ssize_t received;
    char *p;


std::cout << "here befpre\n";
      received = recvfrom(socketFileDir, buf, (ETH_FRAME_LEN), 0, NULL, NULL);
      if (received <= 0)
        break;

std::cout << "here\n";

      //if (memcmp(eh->ether_dhost, if_addr, ETH_ALEN) != 0 && memcmp(eh->ether_dhost, socketAddr.sll_addr, ETH_ALEN) != 0)
      //  continue;

      fprintf(stdout, "%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x ", eh->ether_shost[0], eh->ether_shost[1], eh->ether_shost[2],
              eh->ether_shost[3], eh->ether_shost[4], eh->ether_shost[5], eh->ether_dhost[0], eh->ether_dhost[1], eh->ether_dhost[2],
              eh->ether_dhost[3], eh->ether_dhost[4], eh->ether_dhost[5]);

      received -= sizeof(*eh);
      p = buf + sizeof(*eh);

      
      for (int i = 0; i < received; i++)
        fputc(p[i], stdout);
    

      fputc('\n', stdout);
    }

*/




    char *interfaceName;
    int socketFileDir;
    char buf[ETH_FRAME_LEN];
    int i;

    interfaceName = "enp1s0";
    //memcpy(dest_addr, broadcast_addr, ETH_ALEN);


    /* Create the AF_PACKET socket. */
    if (socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE)) < 0)
    {
        perror("socket()");
        return(1);
    }
        

    struct ifreq ifr;
    int s;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ - 1);

    /* Set interface to promiscuous mode. */
    if (ioctl(socketFileDir, SIOCGIFFLAGS, &ifr) < 0)
    {
        perror("SIOCGIFFLAGS");
        close(socketFileDir);
    }
        
    ifr.ifr_flags |= IFF_PROMISC;

    if (ioctl(socketFileDir, SIOCSIFFLAGS, &ifr) < 0)
    {
        perror("SIOCSIFFLAGS");
        close(socketFileDir);
    }
        

    /* Allow the socket to be reused. */
    s = 1;
    if (setsockopt(socketFileDir, SOL_SOCKET, SO_REUSEADDR, &s, sizeof(s)) < 0)
    {
        perror("SO_REUSEADDR");
        close(socketFileDir);
        return EXIT_FAILURE;
    }

    /* Bind to device. */
    if (setsockopt(socketFileDir, SOL_SOCKET, SO_BINDTODEVICE, interfaceName, IFNAMSIZ - 1) < 0)
    {
        perror("SO_BINDTODEVICE");
        close(socketFileDir);
        return EXIT_FAILURE;
    }

    while (1)
    {
        struct ether_header *eh = (struct ether_header *)buf;
        ssize_t received;
        char *p;

        received = recvfrom(socketFileDir, buf, ETH_FRAME_LEN, 0, NULL, NULL);
        if (received <= 0)
            break;

        fprintf(stdout, "%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x ",
                eh->ether_shost[0], eh->ether_shost[1], eh->ether_shost[2], eh->ether_shost[3], eh->ether_shost[4], eh->ether_shost[5],
                eh->ether_dhost[0], eh->ether_dhost[1], eh->ether_dhost[2], eh->ether_dhost[3], eh->ether_dhost[4], eh->ether_dhost[5]);

        received -= sizeof(*eh);
        p = buf + sizeof(*eh);
        for (i = 0; i < received; i++)
            fputc(p[i], stdout);

        fputc('\n', stdout);
    }

    close(socketFileDir);

        std::cout << "Receiving\n";



        if (passThroughEncode(data) == 1)
        {
            return(RETURN_FAILURE);
        } 

    return (0);
}
