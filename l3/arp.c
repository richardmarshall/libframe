#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "common.h"
#include "pdu.h"
#include "arp.h"
#include "etypes.h"
#include "manip.h"

/* create new arp header */
header_t *arp_header_create(uint16_t htype, uint16_t ptype, uint8_t hsize,
			    uint8_t psize, uint16_t oper, uint8_t *sha, 
			    uint8_t *spa, uint8_t *tha, uint8_t *tpa)
{
	header_t *header = NULL;
	arp_ip_ether_header_t *arp_header = NULL;

	/* return NULL if malloc fails */
	if (!(header = malloc(sizeof(header_t))))
		return NULL;

	/* set header size */
	header->size = sizeof(arp_ip_ether_header_t);

	/* free header and return null if malloc fails */
	if (!(header->data = malloc(header->size))) {
		free(header);
		return NULL;
	}
	
	/* fill arp header */
	arp_header = header->data;
	arp_header->htype = htons(htype);
	arp_header->ptype = htons(ptype);
	arp_header->hlen = hsize;
	arp_header->plen = psize;
	arp_header->oper = htons(oper);
	memcpy((void *)arp_header->sha, (void *)sha, 6);
	memcpy((void *)arp_header->spa, (void *)spa, 4);
	memcpy((void *)arp_header->tha, (void *)tha, 6);
	memcpy((void *)arp_header->tpa, (void *)tpa, 4);

	/* return pointer to new arp header */
	return header;
}

/* create new arp pdu */
pdu_t *arp_create(uint16_t htype, uint16_t ptype, uint8_t hsize, uint8_t psize,
		  uint16_t oper, uint8_t *sha, uint8_t *spa, uint8_t *tha,
		  uint8_t *tpa)
{
	pdu_t *pdu = NULL;
	header_t *header = NULL;

	/* create arp header */
	header = arp_header_create(htype, ptype, hsize, psize, oper, sha, spa,
				   tha, tpa);

	/* if create failed return null */
	if ( header == NULL )
		return NULL;

	/* create pdu, free header, and return either NULL or new pdu */
	pdu = pdu_create(header, NULL);
	free(header);

	return pdu;
}

/* simple fn for IP/Ethernet arp the most common */
pdu_t *arp_ie_simple_create(uint16_t oper, char *sha, char *spa, char *tha,
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
	return arp_create(ARP_HTYPE_ETHERNET, ETYPE_IP, 6, 4, oper, bsha, bspa,
			  btha, btpa);
}
