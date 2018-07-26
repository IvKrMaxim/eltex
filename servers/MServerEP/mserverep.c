#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main () {
    int udpfd = 0, tcpfd = 0, newfd = 0, bytes = 0, epfd = 0, ready = 0, i, op;
    struct sockaddr_in serv_addr;
    struct epoll_event cltfd, readyfd[2];
    char buff[1024];
    if ((tcpfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    if ((udpfd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind (tcpfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 1;
    }
    serv_addr.sin_port = htons (3426);
    if (bind (udpfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 1;
    }
    listen (tcpfd, 10);
    epfd = epoll_create (2);
    if (epfd < 0) {
	printf ("Error create epoll\n");
	return 1;
    }
    cltfd.data.fd = udpfd;
    cltfd.events = EPOLLIN;
    epoll_ctl (epfd, EPOLL_CTL_ADD, udpfd, &cltfd);
    cltfd.data.fd = tcpfd;
    cltfd.events = EPOLLIN | EPOLLET;
    epoll_ctl (epfd, EPOLL_CTL_ADD, tcpfd, &cltfd);
    while (1) {
	ready = epoll_wait (epfd, readyfd, 2, -1);
	for (i = 0; i < ready; i++) {
	    if (readyfd[i].data.fd == tcpfd) {
		newfd = accept (tcpfd, (struct sockaddr*)NULL, NULL);
		if (newfd < 0) {
		    printf ("Error accept\n");
		    return 1;
		}
		recv (newfd, buff, sizeof(buff), 0);
		printf ("%s\n", buff);
		close (newfd);
	    } else {
		bytes = recvfrom (udpfd, buff, sizeof(buff), 0, NULL, NULL);
		buff[bytes] = '\0';
		printf ("%s\n", buff);
	    }
	}
    }
    close (tcpfd);
    close (udpfd);
    return 0;
}