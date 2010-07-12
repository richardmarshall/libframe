#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pdu.h>
#include <common.h>
#include "ether8022llc.h"

/* create a new 802.2LLC header */
struct pdu *ether8022llc_create(struct frame *framep, uint8_t dsap, uint8_t ssap, uint8_t cfield)
{
	struct pdu *pdu = NULL;
	ether8022llc_header_t *llc_header = NULL;

	if ((pdu = create_pdu(framep, sizeof(ether8022llc_header_t), PROTO_ETHER8022LLC))) {
		llc_header = pdu->data;

		/* copy data into new header */
		llc_header->dsap = dsap;
		llc_header->ssap = ssap;
		llc_header->cfield = cfield;
	}
	return pdu;
}
