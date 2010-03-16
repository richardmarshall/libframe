#ifndef __PDUH__
#define __PDUH__

#include <stdint.h>

/* 
 * NOTE: probably would be a good idea to merge these two structs since they are
 * basically the same 
 */
struct pdu {
	uint8_t *data;
	int size;
};
typedef struct pdu pdu_t;

struct header {
	void *data;
	int size;
};
typedef struct header header_t;

pdu_t *pdu_create(header_t *header, pdu_t *payload);

/* free pdu/header functions */
extern void free_pdu(pdu_t **pdu);

/*
 * since both header_t and pdu_t have the same structure just cast input as
 * pdu_t and call pdu_free 
 */
#define free_header(ptr) { free_pdu((pdu_t **)ptr); }

#endif
