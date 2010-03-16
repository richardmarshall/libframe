#ifndef __ARPH__
#define __ARPH__

#include <stdint.h>
#include <pdu.h>

#define ARP_OPER_QUERY   1
#define ARP_OPER_REPLY   2
#define ARP_OPER_RQUERY  3
#define ARP_OPER_RREPLY  4
#define ARP_OPER_IQUERY  8
#define ARP_OPER_IREPLY  9
#define ARP_OPER_NAK     10
#define ARP_HTYPE_ETHERNET 0x0001

/* Probably the only version of this we will create */
struct arp_ip_ether_header {
	uint16_t htype;
	uint16_t ptype;
	uint8_t  hlen;
	uint8_t  plen;
	uint16_t oper;
	uint8_t  sha[6];
	uint8_t  spa[4];
	uint8_t  tha[6];
	uint8_t  tpa[4];
}__attribute__((__packed__));
typedef struct arp_ip_ether_header arp_ip_ether_header_t;


/* function prototypes */
extern header_t *arp_header_create(uint16_t htype, uint16_t ptype,
				   uint8_t hsize, uint8_t psize, uint16_t oper,
				   uint8_t *sha, uint8_t *spa, uint8_t *tha,
				   uint8_t *tpa);

extern pdu_t *arp_create(uint16_t htype, uint16_t ptype, uint8_t hsize,
			 uint8_t psize, uint16_t oper, uint8_t *sha,
			 uint8_t *spa, uint8_t *tha, uint8_t *tpa);

/* simple fn for IP/Ethernet arp the most common */
extern pdu_t *arp_ie_simple_create(uint16_t oper, char *sha, char *spa,
				   char *tha, char *tpa); 


#endif
