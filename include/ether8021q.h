#ifndef __ETHER8021QH__
#define __ETHER8021QH__
#include "pdu.h"

struct dot1q_header
{
	uint16_t pcp_cfi_vid;
	uint16_t etype;
}__attribute__((__packed__));
typedef struct dot1q_header dot1q_header_t;

header_t *dot1q_header_create(uint16_t pcp, uint16_t cfi, uint16_t vid,
			      uint16_t etype);

#define PCP_CFI_VID(p,c,v) (p<<13 | c<<12 | v)

#endif
