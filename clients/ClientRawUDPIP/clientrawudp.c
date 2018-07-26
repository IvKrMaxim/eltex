#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <linux/types.h>

struct headip {
    __u8 vs;
    __u8 tos;
    __u16 tot_len;
    __u16 id;
    __u16 flag_off;
    __u8 ttl;
    __u8 protocol;
    __u16 check;
    __u32 saddr;
    __u32 daddr;
};

struct headudp {
    __u16 sour;
    __u16 dist;
    __u16 len;
    __u16 check;
};

struct package {
    struct headip iphead;
    struct headudp udphead;
    char buff[1024];
};

__u16 checksum (char *buff) {
    __u16 *p, res;
    p = &buff;
    int i = 0, sum = 0;
    for (i = 0; i < 10; i++) {
	sum += p[i];
	sum = (sum >> 16) + (sum & 65535);
    }
    res = sum;
    return res ^ 65535;
}

int main () {
    int fd = 0;
    char buff[1056];
    struct package *sendb, *recvb;
    sendb = buff;
    sendb->iphead.vs = 4 << 4 | 5;
    sendb->iphead.tos = 0;
    sendb->iphead.tot_len = htons(sizeof(struct headip));
    sendb->iphead.id = htons(34444);
    sendb->iphead.flag_off = 0;
    sendb->iphead.ttl = 10;
    sendb->iphead.protocol = 17;
    sendb->iphead.check = 0;
    sendb->iphead.saddr = inet_addr ("192.168.1.100");
    sendb->iphead.daddr = inet_addr ("127.0.0.1");
    sendb->iphead.check = checksum (buff);
    sendb->udphead.sour = htons(3425);
    sendb->udphead.dist = htons(3425);
    sendb->udphead.len = htons(sizeof(struct package) - sizeof (struct headip));
    sendb->udphead.check = 0;
    strcpy (sendb->buff, "Hello, server!");
    struct sockaddr_in serv_addr;
    if ((fd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3426);
    serv_addr.sin_addr.s_addr = inet_addr ("192.168.1.100");
    int opt = 1;
    setsockopt (fd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt));
    if (bind (fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	printf ("Error bind\n");
	return 1;
    }
    serv_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    sendto (fd, buff, sizeof(buff), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    while (1) {
	recvfrom (fd, buff, sizeof(buff), 0, NULL, NULL);
	recvb = buff;
	//if (recvb->udphead.sour == htons (3425))
	printf ("%d %s\n", recvb->udphead.sour, recvb->buff);
    }
    close (fd);
    return 0;
}
