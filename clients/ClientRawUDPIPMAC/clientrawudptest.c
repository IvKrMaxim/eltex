#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <linux/types.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <net/ethernet.h>

struct headeth {
    unsigned char sorce[6];
    unsigned char dist[6];
    __be16 proto;
};

struct headip {
    __u8 ihl:4;
    __u8 vs:4;
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

__u16 checksum (__u16 *p) {
    __u16 res;
    int i = 0, sum = 0;
    for (i = 0; i < 10; i++) {
	sum += p[i];
	sum = (sum >> 16) + (sum & 0xffff);
    }
    res = sum;
    return res ^ 0xffff;
}

int main () {
    int fd = 0;
    char buff[1200];
    memset (buff, 0, sizeof (buff));
    struct ethhdr *machead;
    struct package *s, *r;

    machead = buff;
    s = buff + sizeof(struct headeth);

    machead->h_source[0] = 0xd8;
    machead->h_source[1] = 0xcb;
    machead->h_source[2] = 0x8a;
    machead->h_source[3] = 0xf4;
    machead->h_source[4] = 0x72;
    machead->h_source[5] = 0xb1;

    machead->h_dest[0] = 0xe8;
    machead->h_dest[1] = 0x03;
    machead->h_dest[2] = 0x9a;
    machead->h_dest[3] = 0xb6;
    machead->h_dest[4] = 0xf2;
    machead->h_dest[5] = 0xde;

    machead->h_proto = htons (0x0800);

    s->iphead.vs = 4;
    s->iphead.ihl = 5;
    s->iphead.tos = 0;
    s->iphead.tot_len = htons(sizeof (buff) - sizeof (struct ethhdr));
    s->iphead.id = htons(34444);
    s->iphead.flag_off = 0;
    s->iphead.ttl = 10;
    s->iphead.protocol = 17;
    s->iphead.check = 0;
    s->iphead.saddr = inet_addr ("192.168.1.100");
    s->iphead.daddr = inet_addr ("192.168.1.101");
    s->iphead.check = checksum (buff + 14);

    s->udphead.sour = htons(3426);
    s->udphead.dist = htons(3425);
    s->udphead.len = htons(sizeof (struct package) - sizeof (struct headip));
    s->udphead.check = 0;

    strcpy (s->buff, "Hello, server!");
    
    struct sockaddr_ll serv_addr;
    memset (&serv_addr, 0, sizeof(serv_addr));
    if ((fd = socket (AF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
	printf ("Error: Could not create socket\n");
	return 1;
    }
    serv_addr.sll_family = AF_PACKET;
    serv_addr.sll_ifindex = if_nametoindex ("enp3s0");
    serv_addr.sll_halen = 6;
    int opt = 1;
    //setsockopt (fd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt));
    sendto (fd, buff, sizeof(buff), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    while (1) {
	recvfrom (fd, buff, sizeof(buff), 0, NULL, NULL);
	r = buff + sizeof (struct headeth);
	printf ("%d %s\n", r->udphead.sour, r->buff);
    }
    close (fd);
    return 0;
}
