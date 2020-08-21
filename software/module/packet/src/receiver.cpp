#include <packet/receiver.hpp>

Receiver::Receiver(int idValue, uint8_t **data)
{
    Transfer::setUp(idValue, data);
}


int Receiver::run(memory_data &iterator, uint8_t data[])
{
    char *interfaceName;
    int socketFileDir;
    uint8_t buf[ETH_FRAME_LEN];
    struct ifreq ifr;
    int s;


    interfaceName = "enp1s0";


    /* Create the AF_PACKET socket. */
    if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) < 0)
    {
        perror("socket()");
    }
        

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ - 1);

    /* Set interface to promiscuous mode. */
    if (ioctl(socketFileDir, SIOCGIFFLAGS, &ifr) < 0)
    {
        perror("SIOCGIFFLAGS");
    }
    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl(socketFileDir, SIOCSIFFLAGS, &ifr) < 0)
    {
        perror("SIOCSIFFLAGS");
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

        received = recvfrom(socketFileDir, buf, ETH_FRAME_LEN, 0, NULL, NULL);
        if (received <= 0)
            break;


        fprintf(stdout,
                "%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x \n",
                eh->ether_shost[0],
                eh->ether_shost[1],
                eh->ether_shost[2],
                eh->ether_shost[3],
                eh->ether_shost[4],
                eh->ether_shost[5],
                eh->ether_dhost[0],
                eh->ether_dhost[1],
                eh->ether_dhost[2],
                eh->ether_dhost[3],
                eh->ether_dhost[4],
                eh->ether_dhost[5]);

        passThroughEncode(buf);

    }

    close(socketFileDir);

    return 0;

}
