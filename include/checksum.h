#ifndef _CHECKSUM_H_
#define _CHECKSUM_H_

#include <stdint.h>

uint16_t rfc1071_checksum(void *data, int len);

#endif
