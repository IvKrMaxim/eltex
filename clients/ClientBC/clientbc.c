#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main () {
    int fd = 0;
    char buff[] = "UDP";
    struct sockaddr_in serv_addr;
    if ((fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }

    int broadcast = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
	printf ("Error in setting Broadcast option\n");
        close(fd);
        return 0;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7777);
    serv_addr.sin_addr.s_addr = inet_addr ("255.255.255.255");

    sendto (fd, buff, sizeof(buff), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf ("%s\n", buff);

    close (fd);
    return 0;
}
