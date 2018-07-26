#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main () {
    int fd = 0, bytes = 0;
    struct sockaddr_in serv_addr;
    char buff[1024];
    if ((fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (7777);
    serv_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    if (bind (fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    bytes = recvfrom (fd, buff, sizeof(buff), 0, NULL, NULL);
    buff[bytes] = 0;
    printf ("%s\n", buff);
    close (fd);
    return 0;
}