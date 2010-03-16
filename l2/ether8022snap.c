#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "ether8022snap.h"

/* create a new 802.2SNAP header */
header_t *ether8022snap_header_create(uint32_t ocode, uint16_t pid)
{
	header_t *header = NULL;
	ether8022snap_header_t *snap_header = NULL;

	/* return null if malloc fails */
	if (!(header = malloc(sizeof(header_t))))
		return NULL;

	/* free header and return null if malloc fails */
	if (!(header->data = malloc(sizeof(ether8022snap_header_t)))) {
		free(header);
		return NULL;
	}

	/* set size in generic header */
	header->size = sizeof(ether8022snap_header_t);
	snap_header = header->data;

	/* prep ocode */
	ocode = htonl(ocode) >> 8;

	/* copy data into new header */
	memcpy((void *)snap_header->ocode, (void *)&ocode, 3);
	snap_header->pid = htons(pid);

	return header;
}
