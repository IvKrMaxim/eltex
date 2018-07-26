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
    int udpfd = 0, tcpfd = 0, newfd = 0, bytes = 0, ready, cntc = 1, i;
    int cltfd[100];
    struct sockaddr_in serv_addr, con_addr;
    struct pollfd cfd[101];
    char buff[1024];
    if ((udpfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind (udpfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    while (1) {
	memset (cfd, 0, sizeof(cfd));
	cfd[0].fd = udpfd;
	cfd[0].events = POLLRDNORM;
	for (i = 1; i < cntc; i++) {
	    cfd[i].fd = cltfd[i - 1];
	    cfd[i].events = POLLRDNORM;
	}
	ready = poll (cfd, cntc, -1);
	if (cfd[0].revents == POLLRDNORM) {
	    if ((cltfd[cntc - 1] = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf ("Error: could not create socket\n");
		return 1;
	    }
	    socklen_t len = sizeof(con_addr);
	    recvfrom (udpfd, buff, sizeof(buff), 0, (struct sockaddr*)&con_addr, &len);
	    sendto (cltfd[cntc - 1], buff, sizeof(buff), MSG_WAITALL, (struct sockaddr*)&con_addr, len);
	    printf ("%s\n", buff);
	    cntc++;
	}
	for (i = 1; i < cntc; i++) {
	    if (cfd[i].revents == POLLRDNORM) {
		bytes = recvfrom (cfd[i].fd, buff, sizeof(buff), 0, NULL, NULL);
	        buff[bytes - 1] = '\0';
	        printf ("%s", buff);
	    }
	}	
    }
    close (udpfd);
    for (i = 0; i < cntc; i++) {
	close (cltfd[i]);
    }
    return 0;
}