#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main () {
    int fd = 0, newfd = 0, i = 0;
    struct sockaddr_in serv_addr;
    char buff[1024];
    char addr[] = "127.0.0.1";
    if ((fd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
	printf ("Error: could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (3425);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind (fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 0;
    }
    listen (fd, 100);
    while (1) {
	newfd = accept (fd, (struct sockaddr*)NULL, NULL);
	if (newfd < 0) {
	    printf ("Error accept\n");
	    return 1;
	}
	sprintf (buff, "count %d", i);
	send (newfd, buff, sizeof(buff), MSG_WAITALL);
	close (newfd);
	i++;
    }
    close (fd);
    return 0;
}