#ifndef __ETHER8022SNAPH__
#define __ETHER8022SNAPH__

#include <stdint.h>
#include "pdu.h"
#include <protos.h>

/* SNAP Ogranization Codes */
#define SNAP_OCODE_CISCO 0x00000c

/* SNAP PIDs */
#define SNAP_PID_PVST 0x010b

struct ether8022snap_header {
	uint8_t ocode[3];
	uint16_t pid;
}__attribute__((__packed__));
typedef struct ether8022snap_header ether8022snap_header_t;

int ether8022snap_create(struct frame *framep, uint32_t ocode, uint16_t pid);

#endif
