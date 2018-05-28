// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> 
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_ll address = {0};
    struct sockaddr eth_addr = {0};
    int opt = 1;
    int addrlen = sizeof(address);
    unsigned char buffer[2048] = {0};
     
    if (argc < 2 || argv[1] == NULL)
    {
        printf("error: invaild args, please enter tap interface name\n");
        exit(EXIT_FAILURE);
    }
 
    // Creating socket file descriptor
    if ((server_fd = socket(PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) <= 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

	address.sll_family   = PF_PACKET;
	address.sll_halen    = ETHER_ADDR_LEN;
	address.sll_ifindex  = if_nametoindex(argv[1]);
	address.sll_protocol = htons(ETH_P_ALL);
	address.sll_hatype   = 0;
	address.sll_pkttype  = PACKET_HOST;
      
    printf("bind() to %s ifindex %d \n", eth_addr.sa_data, address.sll_ifindex);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_ll)) != 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

	while(1){
    valread = read( server_fd , buffer, 2048);
    printf("read %d bytes data: %02x %02x %02x %02x %02x %02x %02x %02x\n", valread, buffer[0], buffer[1], buffer[2], buffer[3],
		buffer[4], buffer[5], buffer[6], buffer[7] );
	}

    return 0;
}
