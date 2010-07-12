#ifndef __PDUH__
#define __PDUH__

#include <stdint.h>

struct frame {
	int tsize;
	int size; 
	struct pdu *pdus; 
	void *data;
	void *payload; 
};

struct pdu {
	void *data;
	short type;
	int size;
	struct pdu *next;
};

extern void free_frame(struct frame **framep);
extern struct pdu *create_pdu(struct frame *framep, size_t size, short type);
extern struct frame *create_frame(size_t size);

#endif
