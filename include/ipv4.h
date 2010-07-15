#ifndef _IPV4_H_
#define _IPV4_H_

#include <stdint.h>
#include <pdu.h>
#include <checksum.h>

struct ipv4 {
	uint8_t ver_head_len;
	uint8_t diff_serv;
	uint16_t total_length;
	uint16_t ident;
	uint16_t flags_frag_offset;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t src;
	uint32_t dst;
} __attribute__((__packed__));
typedef struct ipv4 ipv4_t;

#define VER_HEADLEN(v, hl) ((v & 0xf) << 4 | (hl & 0xf))
#define FLAGS_FRAGOFF(f, fo) (((f & 0x0007) << 13) | (fo & 0x3FFF))

#define DF 2
#define MF 1

inline uint8_t ipv4_get_header_length(ipv4_t *header)
{
	return header->ver_head_len & 0x0F;
}

inline uint8_t ipv4_get_version(ipv4_t *header)
{
	return (header->ver_head_len & 0xF0) >> 4;
}

inline uint8_t ipv4_get_flags(ipv4_t *header)
{
	return (header->flags_frag_offset & 0xE000) >> 13;
}

inline uint16_t ipv4_get_frag_offset(ipv4_t *header)
{
	return header->flags_frag_offset & 0x3FFF;
}

inline void ipv4_set_header_length(ipv4_t *header, uint8_t len)
{
	header->ver_head_len |= len & 0xF;
}

inline void ipv4_set_version(ipv4_t *header, uint8_t ver)
{
	header->ver_head_len |= ((ver & 0xF) << 4);
}

inline void ipv4_set_flags(ipv4_t *header, uint8_t flags)
{
	header->flags_frag_offset |= ((flags & 0x0007) << 13);
}

inline void ipv4_set_frag_offset(ipv4_t *header, uint16_t frag)
{
	header->flags_frag_offset |= frag & 0x3FFF;
}

/* 
 * Does not modify the ip header passed in so make sure the checksum field
 * is already set to 0 
 */
inline uint16_t ipv4_checksum(ipv4_t *header)
{
	return rfc1071_checksum((void *)header, ipv4_get_header_length(header)*4);
}

struct pdu *ipv4_create(struct frame *fp, uint8_t diff_serv, uint16_t ident,
			uint8_t flags, uint16_t fragoff, uint8_t ttl, 
			uint8_t proto, uint32_t src, uint32_t dst);
struct pdu *ipv4_simple_create(struct frame *fp, uint8_t diff_serv,
				uint16_t ident, uint8_t flags, uint16_t fragoff,
				uint8_t ttl, uint8_t proto, char *src, 
				char *dst);

#endif
