#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main () {
    int fd = 0;
    char buff[] = "Connect";
    struct sockaddr_in serv_addr;
    struct sockaddr con_addr;
    socklen_t len = sizeof(con_addr);;
    if ((fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3425);
    serv_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");

    sendto (fd, buff, sizeof(buff), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    recvfrom (fd, buff, sizeof(buff), 0, &con_addr, &len);
    printf ("%s\n", buff);
    while (1) {
	fgets (buff, sizeof(buff), stdin);
	sendto (fd, buff, sizeof(buff), MSG_WAITALL, &con_addr, len);
    }
    close (fd);
    return 0;
}
