#ifndef __ETHER8023H__
#define __ETHER8023H__

#include <stdint.h>
#include "pdu.h"
#include "etherii.h"

/* since a 802.3 header is structured exactly the same as etherII just creating a new typedef */
typedef struct etherii_header ether8023_header_t;

/* inline function to wrap etherii function with 8023 name */
inline header_t *ether8023_header_create( uint8_t *dst, uint8_t *src, uint16_t len )
{
	return etherii_header_create( dst, src, len );
}

/* inline function to wrap etherii function with 8023 name */
inline header_t *ether8023_simple_header_create( char *dst, char *src, uint16_t len )
{
	return etherii_simple_header_create( dst, src, len );
}

#endif
