#include "etherii.h"
#include "manip.h"
#include <stdlib.h>
#include <string.h>

extern int	set_etherii_header(char *dst, char *src, int etype, char *buf) {
	char mac_dst[6], mac_src[6];

	if ( !parse_mac_string(dst, mac_dst) )
		exit(1);
	if ( !parse_mac_string(src, mac_src) )
		exit(2);

	memcpy((void *)buf, (void *)mac_dst, (sizeof(char)*6));
	memcpy((void *)(buf+6), (void *)mac_src, (sizeof(char)*6));
	memcpy((void *)(buf+12), (void *)&etype, (sizeof(char)*2));
	return 14;
}
