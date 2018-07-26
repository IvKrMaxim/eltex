#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main () {
    int udpfd = 0, tcpfd = 0, newfd = 0, bytes = 0;
    struct sockaddr_in serv_addr;
    char buff[1024];
    char addr[] = "127.0.0.1";
    if ((tcpfd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    if ((udpfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind (tcpfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    serv_addr.sin_port = htons (3426);
    if (bind (udpfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    int maxfd;
    if (tcpfd > udpfd)
	maxfd = tcpfd;
    else
	maxfd = udpfd;
    listen (tcpfd, 10);
    while (1) {
	fd_set readfd;
	FD_ZERO (&readfd);
	FD_SET (tcpfd, &readfd);
	FD_SET (udpfd, &readfd);
	struct timeval tv;
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	select (maxfd + 1, &readfd, NULL, NULL, &tv);
	if (FD_ISSET (tcpfd, &readfd)) {
	    newfd = accept (tcpfd, (struct sockaddr*)NULL, NULL);
	    if (newfd < 0) {
		printf ("Error accept\n");
	        return 1;
	    }
	    bytes = recv (newfd, buff, sizeof(buff), 0);
	    buff[bytes] = '\0';
	    printf ("%s\n", buff);
	    close (newfd);
	}
	if (FD_ISSET (udpfd, &readfd)) {
	    bytes = recvfrom (udpfd, buff, sizeof(buff), 0, NULL, NULL);
	    buff[bytes] = '\0';
	    printf ("%s\n", buff);
	}
    }
    close (tcpfd);
    close (udpfd);
    return 0;
}