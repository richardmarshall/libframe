#ifndef __8023H__
#define __8023H__

#include "pdu.h"
#include "common.h"

struct ether8023_header {
	    u8_t dst[6];
		u8_t src[6];
		u16_t length;
}__attribute__((__packed__));
typedef struct ether8023_header ether8023_header_t;

header_t *ether8023_header_create( u8_t *dst, u8_t *src, u16_t length );
header_t *ether8023_simple_header_create( u8_t *dst, u8_t *src, u16_t length );

#endif
