#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <linux/types.h>

struct headudp {
    __u16 sour;
    __u16 dist;
    __u16 len;
    __u16 check;
};

struct package {
    struct headudp head;
    char buff[1024];
};

int main () {
    int fd = 0;
    char recvbuff[1052];
    struct package sendb, *recvb;
    sendb.head.sour = htons(3444);
    sendb.head.dist = htons(3425);
    sendb.head.len = htons(sizeof(struct package));
    sendb.head.check = 0;
    strcpy (sendb.buff, "Hello, server!");
    struct sockaddr_in serv_addr;
    if ((fd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3425);
    serv_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");

    sendto (fd, &sendb, sizeof(sendb), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    while (1) {
	recvfrom (fd, recvbuff, sizeof(recvbuff), 0, NULL, NULL);
	recvb = recvbuff + 20;
	if (recvb->head.sour == htons (3425))
	    printf ("%d %s\n", recvb->head.sour, recvb->buff);
    }
    close (fd);
    return 0;
}
