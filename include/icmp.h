#ifndef _ICMP_H_
#define _ICMP_H_

#include <stdint.h>
#include <pdu.h>

/* Non exhaustive list of icmp types */
#define ICMP_ECHO_REPLY 0
#define ICMP_RES1 1
#define ICMP_RES2 2
#define ICMP_DEST_UNREACHABLE 3
#define ICMP_SOURCE_QUENCH 4
#define ICMP_REDIRECT 5
#define ICMP_ALT_HOST_ADDR 6
#define ICMP_RES7 7
#define ICMP_ECHO_REQUEST 8
#define ICMP_ROUTER_ADV 9
#define ICMP_ROUTER_SOL 10
#define ICMP_TIME_EXCEEDED 11
#define ICMP_BAD_IP_HEAD 12
#define ICMP_TIMESTAMP 13
#define ICMP_TIMESTAMP_REPLY 14
#define ICMP_INFO_REQUEST 15
#define ICMP_INFO_REPLY 16
#define ICMP_ADDR_MASK_REQUEST 17
#define ICMP_ADDR_MASK_REPLY 18
#define ICMP_TRACEROUTE 30

/* Non exhusting list if icmp codes */
#define ICMP_NOCODE 0
#define ICMP_NETWORK_UNREACHABLE 1
#define ICMP_HOST_UNREACHABLE 2
#define ICMP_PROTOCOL_UNREACHABLE 3
#define ICMP_FRAG_REQUIRED 4
#define ICMP_SOURCE_ROUTE_FAILED 5
#define ICMP_DEST_NET_UNKNOWN 6
#define ICMP_DEST_HOST_UNKNOWN 7
#define ICMP_SRC_HOST_ISOLATED 8
#define ICMP_NET_ADMIN_PROHIBITED 9
#define ICMP_HOST_ADMIN_PROHIBITED 10
#define ICMP_NET_UNREACHABLE_TOS 11
#define ICMP_HOST_UNREACHABLE_TOS 12
#define ICMP_COMMUNICATION_ADMIN_PROHIBITED 13
#define ICMP_REDIRECT_NET 0
#define ICMP_REDIRECT_HOST 1
#define ICMP_REDIRECT_TOS_NET 2
#define ICMP_REDIRECT_TOS_HOST 3
#define ICMP_TTL_EXPIRED 0
#define ICMP_FRAG_ASSEMBLY_TIME_EXCEEDED 1

struct icmp {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t sequence;
}__attribute__((__packed__));
typedef struct icmp icmp_t;


struct pdu *icmp_create(struct frame *fp, uint8_t type, uint8_t code, 
			uint16_t id, uint16_t sequence, size_t padlen);

#endif
