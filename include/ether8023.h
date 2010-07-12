#ifndef __ETHER8023H__
#define __ETHER8023H__

#include <stdint.h>
#include "pdu.h"
#include "etherii.h"
#include <protos.h>

/*

Usage example (where layer3 is already created pdu_t* for layer3 protocol data):

char *dst = "00:00:00:00:00:00";
char *src = "00:00:00:00:00:00";
header_t *ether_header = NULL;
pdu_t *ether_frame = NULL;

ether_header = etherii_simple_header_create( dst, src, layer3->size );
ether_frame = pdu_create( ether_header, layer3 );

*/

/* inline function to wrap etherii function with 8023 name */
inline int ether8023_create(struct frame *framep, uint8_t *dst, uint8_t *src)
{
	return etherii_create(framep, dst, src, framep->size);
}

/* inline function to wrap etherii function with 8023 name */
inline int ether8023_simple_create(struct frame *framep, char *dst, char *src)
{
	return etherii_simple_create(framep, dst, src, framep->size);
}

#endif
