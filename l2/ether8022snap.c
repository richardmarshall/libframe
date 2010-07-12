#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <common.h>
#include "ether8022snap.h"

/* create a new 802.2SNAP header */
struct pdu *ether8022snap_create(struct frame *framep, uint32_t ocode, uint16_t pid)
{
	struct pdu *pdu = NULL;
	ether8022snap_header_t *snap_header = NULL;

	if ((pdu = create_pdu(framep, sizeof(ether8022snap_header_t), PROTO_ETHER8022SNAP))) {
		snap_header = pdu->data;

		/* prep ocode */
		ocode = htonl(ocode) >> 8;

		/* copy data into new header */
		memcpy((void *)snap_header->ocode, (void *)&ocode, 3);
		snap_header->pid = htons(pid);
	}
	return pdu;
}
