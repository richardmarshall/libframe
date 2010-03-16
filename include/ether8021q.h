#ifndef __ETHER8021QH__
#define __ETHER8021QH__

struct dot1q_header
{
	uint16_t tpid;
	union {
		uint16_t pcp_cfi_vid;
		struct {
			uint16_t pcp : 3;
			uint16_t cfi : 1;
			uint16_t vid : 12;
		};
	};
	uint16_t etype;
}__attribute__((__packed__));
typedef struct dot1q_header dot1q_header_t;

#endif
