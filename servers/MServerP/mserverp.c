#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main () {
    int udpfd = 0, tcpfd = 0, newfd = 0, bytes = 0, ready;
    struct sockaddr_in serv_addr;
    struct pollfd cltfd[2];
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
    listen (tcpfd, 10);
    while (1) {
	cltfd[0].fd = tcpfd;
	cltfd[0].events = POLLRDNORM;
	cltfd[1].fd = udpfd;
	cltfd[1].events = POLLRDNORM;
	ready = poll (cltfd, 2, -1);
	if (cltfd[0].revents & POLLRDNORM) {
	    newfd = accept (tcpfd, (struct sockaddr*)NULL, NULL);
	    if (newfd < 0) {
		printf ("Error accept\n");
	        return 1;
	    }
	    recv (newfd, buff, sizeof(buff), 0);
	    printf ("%s\n", buff);
	    close (newfd);
	}
	if (cltfd[1].revents & POLLRDNORM) {
	    bytes = recvfrom (udpfd, buff, sizeof(buff), 0, NULL, NULL);
	    buff[bytes] = '\0';
	    printf ("%s\n", buff);
	}
    }
    close (tcpfd);
    close (udpfd);
    return 0;
}