#include <stdint.h>
#include <stddef.h>
#include <checksum.h>

/* 
 * Simple implementation of rcf1071 based mostly on the
 * reference algorithm.
 */
uint16_t rfc1071_checksum(void *data, int len)
{
	uint16_t *p = NULL;
	register uint32_t sum = 0;

	/* sum up header */
	for (p = data; len > 1; len -= 2)
		sum += *p++;

	/* handle len % 2 != 0 */
	if (len > 0)
		sum += *(uint8_t *)p;

	/* fold */
	while(sum>>16)
		sum = (sum & 0xffff) + (sum >> 16);

	return (uint16_t)~sum;
}

