#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "common.h"
#include "pdu.h"
#include "arp.h"
#include "etypes.h"
#include "manip.h"

/* create new arp header */
struct pdu *arp_create(struct frame *framep, uint16_t htype, uint16_t ptype, uint8_t hsize,
			    uint8_t psize, uint16_t oper, uint8_t *sha, 
			    uint8_t *spa, uint8_t *tha, uint8_t *tpa)
{
	struct pdu *pdu = NULL;
	arp_ip_ether_header_t *arp_header = NULL;

	if ((pdu = create_pdu(framep, sizeof(arp_ip_ether_header_t), PROTO_ARP))) {
		arp_header = pdu->data;
		/* fill arp header */
		arp_header->htype = htons(htype);
		arp_header->ptype = htons(ptype);
		arp_header->hlen = hsize;
		arp_header->plen = psize;
		arp_header->oper = htons(oper);
		memcpy((void *)arp_header->sha, (void *)sha, 6);
		memcpy((void *)arp_header->spa, (void *)spa, 4);
		memcpy((void *)arp_header->tha, (void *)tha, 6);
		memcpy((void *)arp_header->tpa, (void *)tpa, 4);
	}
	return pdu;
}

/* simple fn for IP/Ethernet arp the most common */
struct pdu *arp_ie_simple_create(struct frame *framep, uint16_t oper, char *sha, char *spa, char *tha,
			    char *tpa)
{
	uint8_t bsha[6], btha[6];
	uint8_t bspa[4], btpa[4];

	/* convert strings */
	if (!parse_mac_string(sha, bsha)) 
		return NULL;
	if (!parse_mac_string(tha, btha))
		return NULL;
	if (!parse_ip_string(spa, bspa))
		return NULL;
	if (!parse_ip_string(tpa, btpa))
		return NULL;

	/* return results of arp_create */
	return arp_create(framep, ARP_HTYPE_ETHERNET, ETYPE_IP, 6, 4, oper, bsha, bspa,
			  btha, btpa);
}
