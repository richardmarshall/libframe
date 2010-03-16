#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "etherii.h"
#include "manip.h"

/* create a new etherii header */
header_t *etherii_header_create(uint8_t *dst, uint8_t *src, uint16_t etype) {
	header_t *header = NULL;
	etherii_header_t *ether_header = NULL;

	/* return NULL if malloc fails */
	if (!(header = malloc(sizeof(header_t))))
		return NULL;

	/* free header and return NULL if malloc fails */
	if (!(header->data = malloc(sizeof(etherii_header_t)))) {
		free(header);
		return NULL;
	}

	/* set size in generic header struct */
	header->size = sizeof(etherii_header_t);
	ether_header = header->data;

	/* copy data into new header */
	memcpy((void *)ether_header->dst, (void *)dst, 6);
	memcpy((void *)ether_header->src, (void *)src, 6);
	ether_header->etype = htons(etype);

	/* return pointer to new header */
	return header;
}

/* simple create header takes string arguments for src/dst macs */
header_t *etherii_simple_header_create(char *dst, char *src, uint16_t etype) {
	uint8_t bdst[6], bsrc[6];

	/* convery MAC string to internal representation */
	if (!parse_mac_string(dst, bdst))
		return NULL;
	if (!parse_mac_string(src, bsrc))
		return NULL;

	return etherii_header_create(bdst, bsrc, etype);	
}
