#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "ether8021q.h"

/* Create 802.1q header */

header_t *dot1q_header_create(uint16_t pcp, uint16_t cfi, uint16_t vid, uint16_t etype)
{
	header_t *header = NULL;
	dot1q_header_t *dot1q_h = NULL;

	/* return null if malloc fails */
	if (!(header = malloc(sizeof(header_t))))
		return NULL;

	/* free header and return null if malloc fails */
        if (!(header->data = malloc(sizeof(dot1q_header_t)))) {
                free(header);
                return NULL;
	}

        /* set size in generic header */
        header->size = sizeof(dot1q_header_t);
        dot1q_h = header->data;

        /* copy data into new header */
        dot1q_h->pcp = pcp;
        dot1q_h->cfi = cfi;
        dot1q_h->vid = vid;
	dot1q_h->etype = etype;

        return header;
}

