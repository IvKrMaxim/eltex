#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main () {
    int fd = 0;
    char buff[] = "TCP";
    struct sockaddr_in serv_addr;
    if ((fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error: Connect Failed\n");
	return 1;
    }
    send (fd, buff, sizeof(buff), MSG_WAITALL);
    printf ("%s\n", buff);

    close (fd);
    return 0;
}
