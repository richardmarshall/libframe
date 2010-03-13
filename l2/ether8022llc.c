#include "ether8022llc.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

/* create a new 802.2LLC header */
header_t *ether8022llc_header_create( uint8_t dsap, uint8_t ssap, uint8_t cfield )
{
	header_t *header = NULL;
	ether8022llc_header_t *llc_header = NULL;

	/* return null if malloc fails */
	if ( !(header = malloc( sizeof(header_t))))
		return NULL;

	/* free header and return null if malloc fails */
	if ( !(header->data = malloc(sizeof(ether8022llc_header_t)))) {
		free(header);
		return NULL;
	}

	/* set size in generic header */
	header->size = sizeof(ether8022llc_header_t);
	llc_header = header->data;

	/* copy data into new header */
	llc_header->dsap = dsap;
	llc_header->ssap = ssap;
	llc_header->cfield = cfield;

	return header;
}
