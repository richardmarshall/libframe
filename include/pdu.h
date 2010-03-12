#ifndef __PDUH__
#define __PDUH__

#include "common.h"

struct pdu {
	u8_t *data;
	int size;
};
typedef struct pdu pdu_t;

struct header {
	void *data;
	int size;
};
typedef struct header header_t;

pdu_t *pdu_create( header_t *header, pdu_t *payload );

#endif
