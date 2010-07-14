#ifndef __PDUH__
#define __PDUH__

#include <stddef.h>

struct frame {
	size_t tsize;
	size_t size; 
	struct pdu *pdus; 
	void *data;
	void *payload; 
};

struct pdu {
	void *data;
	short type;
	size_t size;
	struct pdu *next;
};

extern void free_frame(struct frame **framep);
extern struct pdu *create_pdu(struct frame *framep, size_t size, short type);
extern struct frame *create_frame(size_t size);

#endif
