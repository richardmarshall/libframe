#ifndef __ARPH__
#define __ARPH__

#define ARP_OPER_QUERY 0x0100
#define ARP_OPER_REPLY 0x0200
#define ARP_HTYPE_ETHERNET 0x0100

struct arp {
	short htype;
	short ptype;
	char hlen;
	char plen;
	short oper;
	char sha[6];
	char spa[4];
	char tha[6];
	char tpa[4];
} __attribute__((__packed__));
typedef struct arp arp_t;

extern int build_arp(arp_t *arp, int offset, char *frame);
extern int set_arp(char *s_mac, char *s_ip, char *d_mac, char *d_ip, short oper, int offset, char *frame);

#endif
