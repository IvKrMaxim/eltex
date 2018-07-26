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
    struct sockaddr_in serv_addr, cli_addr;
    char buff[1024];
    if ((fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.100");
    if (bind (fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    while (1) {
	socklen_t len = sizeof (cli_addr);
	bytes = recvfrom (fd, buff, sizeof(buff), 0, (struct sockaddr*)&cli_addr, &len);
	buff[bytes] = '\0';
	printf ("%s\n", buff);
	strcpy (buff + 7, "client!");
	sendto (fd, buff, sizeof(buff), 0, (struct sockaddr*)&cli_addr, len);
    }
    close (fd);
    return 0;
}
