// Server side C/C++ program to demonstrate Socket programming
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> 

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, numbytes, nsfd;
    struct sockaddr_in address ={0};
    int opt = 1;
    int addrlen = sizeof(address);
    unsigned char buffer[1024] = {0};
    char network_stack[50] = {0};
    char tapif[10];
    
	if(argv[1] == NULL || argv[2] == NULL)
	{
		printf("enter tap interface and ip address eg ./receive_inet tap0 192.168.1.10 \n");
	    exit(EXIT_FAILURE);
	}
	strcpy(tapif, argv[1]);
	int device_index = atoi(&tapif[3]);
	sprintf(network_stack, "/var/run/netns/ns%d", device_index);
	nsfd = open(network_stack, O_RDONLY);  /* Get descriptor for namespace */
	if (nsfd == -1)
	{
	   printf("open() error\n");
	   exit(EXIT_FAILURE);
	}
	if (setns(nsfd, 0) == -1)        /* Join that namespace */
	{
	   printf("setns() error\n");
	   exit(EXIT_FAILURE);
	}

    // Creating socket file descriptor, IPPROTO_ICMP,  htons(ETH_P_ALL)
    if ((server_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[2]);
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    for(;;){
       numbytes = recvfrom(server_fd, buffer, 1024, 0, NULL, NULL);
       printf("listener: got packet %lu bytes\n", numbytes);
       printf("received %x %x %x %x %x %x %x %x \n", buffer[0], buffer[1],buffer[2],buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
    }
    return 0;
}
