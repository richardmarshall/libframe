#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <common.h>
#include "ether8021q.h"

/* Create 802.1q header */
int dot1q_create(struct frame *framep, uint16_t pcp, uint16_t cfi, uint16_t vid,
			      uint16_t etype)
{
	struct pdu *pdu = NULL;
	dot1q_header_t *dot1q_h = NULL;
        if ((pdu = create_pdu(framep, sizeof(dot1q_header_t), PROTO_ETHER8021Q))) {
		dot1q_h = pdu->data;
		/* copy data into new header */
		/*
		 * unfortunantly the bit field idea will not work as the pcp,cfi and a 
		 * portion of the vid fields need to be in the high order bits of the 
		 * bit not the low order so either we would need to split the field
		 * into 2 uint8_t bit fields and split the vid into the various bits
		 * or bit shift the various pieces into the right place and | them
		 * together
		 */
		dot1q_h->pcp_cfi_vid = PCP_CFI_VID(pcp, cfi, vid);
		dot1q_h->pcp_cfi_vid = htons(dot1q_h->pcp_cfi_vid);
		dot1q_h->etype = htons(etype);
		return true;
	}
        return false;
}

