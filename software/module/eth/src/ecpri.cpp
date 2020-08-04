#include <eth/ecpri.hpp>

void Transport::getData()
{
    sendTrans->ecpriVersion = 1; // Version 1
    sendTrans->ecpriMessage = 0; // IQ data type
    sendTrans->ecpriConcatenation = 0; // No concatenation
    //sendTrans->ecpriPayload = sizeof(); // Size of payload


}

int Transport::setUpEth()
{
    int socketFileDir;
	struct ifreq interfaceIndex // Interface index
	struct ifreq MACInterface; // MAC interface

	struct sockaddr_ll socketAddr;

	char interfaceName[IFNAMSIZ] = DEFAULT_IF;
    // IFNAMSIZ is the maxomum buffer size needed to hold an interface name including the terminating 0
	

	/* Open RAW socket to send on */
	if ((socketFileDir = socket(AF_PACKET, SOCK_RAW, 0)) == -1) 
    {
	    std::cout << "socket opening error\n";
        return(1);
	}


	/* Get the index of the interface to send on */
	memset(&interfaceIndex, 0, sizeof(struct ifreq)); // Sets value of interfaceIndex to 0 the size of ifreq

	strncpy(interfaceIndex.ifr_name, interfaceName, IFNAMSIZ-1); 
    // Copies interfaceName to interfaceIndex struct, size of max buffer size minus the terminating 0

    // Manipulates underlying device parameters of special files ????, typically to control the termincal
    // SIOGCGIFINDEX gets the index of the interface into socketFileDir
    if (ioctl(socketFileDir, SIOCGIFINDEX, &interfaceIndex) < 0)
    {
        std::cout << "IOCTL error\n";
        return(1);
    }


	/* Get the MAC address of the interface to send on */
	memset(&MACInterface, 0, sizeof(struct ifreq));

	strncpy(MACInterface.ifr_name, interfaceName, IFNAMSIZ-1);

    // SIOCGIFHWADDR gets the address of a device using socketFileDir
	if (ioctl(socketFileDir, SIOCGIFHWADDR, &MACInterface) < 0)
	{
        std::cout << "IOCTL error\n";
        return(1);
    }


    return(0);
}