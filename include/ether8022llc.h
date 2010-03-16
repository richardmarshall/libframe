#ifndef __ETHER8022LLCH__
#define __ETHER8022LLCH__

#include <stdint.h>
#include "pdu.h"

/* LLC SAPs */
#define SAP_SNAP 0xAA
#define SAP_BPDU 0x42

/* LLC Control field flags */
#define CFIELD_UNNUMBERED_INFO 0x00
#define CFIELD_UNNUMBERED_FRAME 0x03

struct ether8022llc_header {
	uint8_t dsap;
	uint8_t ssap;
	uint8_t cfield;
}__attribute__((__packed__));
typedef struct ether8022llc_header ether8022llc_header_t;

header_t *ether8022llc_header_create(uint8_t dsap, uint8_t ssap, uint8_t cfield);

static inline pdu_t *ether8022llc_quick_create( uint8_t dsap, uint8_t ssap,
						uint8_t cfield, pdu_t *payload )
{
	return pdu_create(ether8022llc_header_create(dsap, ssap, cfield), payload);
}

#endif
