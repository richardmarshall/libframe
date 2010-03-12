#ifndef __ETHERIIH__
#define __ETHERIIH__

#include <stdint.h>
#include "pdu.h"

struct etherii_header {
	uint8_t  dst[6];
	uint8_t  src[6];
	uint16_t etype;
}__attribute__((__packed__));
typedef struct etherii_header etherii_header_t;

header_t *etherii_header_create( uint8_t *dst, uint8_t *src, uint16_t etype );
header_t *etherii_simple_header_create( char *dst, char *src, uint16_t etype );

#endif
