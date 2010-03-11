#ifndef __ETHERIIH__
#define __ETHERIIH__

struct etherii_header_s {
	long dest;
	long source;
	short etype;
};
typedef struct etherii_header_s etherii_header_t;

int	set_etherii_header(char *dst, char *src, int etype, char *buf);

#endif
