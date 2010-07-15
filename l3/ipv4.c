#include <stddef.h>
#include <arpa/inet.h>
#include <checksum.h>
#include <ipv4.h>
#include <protos.h>
#include <manip.h>

/*
 * Current implementation does not support ipv4 header options.
 */
struct pdu *ipv4_create(struct frame *fp, uint8_t diff_serv, uint16_t ident,
			uint8_t flags, uint16_t fragoff, uint8_t ttl, 
			uint8_t proto, uint32_t src, uint32_t dst)
{
	struct pdu *pdu = NULL;
	ipv4_t *ip = NULL;

	if ((pdu = create_pdu(fp, sizeof(ipv4_t), PROTO_IPV4))) {
		ip = pdu->data;
		ip->ver_head_len = VER_HEADLEN(4, 5);
		ip->diff_serv = diff_serv;
		ip->total_length = htons(fp->size);
		ip->ident = htons(ident);
		ip->flags_frag_offset = htons(FLAGS_FRAGOFF(flags, fragoff));
		ip->ttl = ttl;
		ip->protocol = proto;
		ip->src = src;
		ip->dst = dst;
		ip->checksum = 0;
		ip->checksum = ipv4_checksum(ip);
	}
	return pdu;
}

struct pdu *ipv4_simple_create(struct frame *fp, uint8_t diff_serv,
				uint16_t ident, uint8_t flags, uint16_t fragoff,
				uint8_t ttl, uint8_t proto, char *src, 
				char *dst)
{
	uint32_t bsrc, bdst;

	if (!parse_ip_string(src, (uint8_t *)&bsrc))
		return NULL;
	if (!parse_ip_string(dst, (uint8_t *)&bdst))
		return NULL;

	return ipv4_create(fp, diff_serv, ident, flags, fragoff, ttl,
							proto, bsrc, bdst);
}

