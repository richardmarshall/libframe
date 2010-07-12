#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "etherii.h"
#include "manip.h"
#include "pdu.h"

struct pdu *etherii_create(struct frame *framep, uint8_t *dst, uint8_t *src, uint16_t etype)
{
	struct pdu *pdu = NULL;
	etherii_header_t *ether_header = NULL;
	if ((pdu = create_pdu(framep, sizeof(etherii_header_t), PROTO_ETHERII))) {
		ether_header = pdu->data;
		memcpy((void *)ether_header->dst, (void *)dst, 6);
		memcpy((void *)ether_header->src, (void *)src, 6);
		ether_header->etype = htons(etype);
	} 
	return pdu;
}

struct pdu *etherii_simple_create(struct frame *framep, char *dst, char *src, uint16_t etype)
{
	uint8_t bdst[6], bsrc[6];

	/* convery MAC string to internal representation */
	if (!parse_mac_string(dst, bdst))
		return NULL;
	if (!parse_mac_string(src, bsrc))
		return NULL;

	return etherii_create(framep, bdst, bsrc, etype);	
}
