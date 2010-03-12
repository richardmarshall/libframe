#include <string.h>
#include "arp.h"
#include "etypes.h"
#include "manip.h"

int build_arp(arp_t *arp, int offset, char *frame) {
	memcpy((void *)(frame+offset), (void *)arp, sizeof(arp_t));
	return offset+sizeof(arp_t);
}

int set_arp(char *s_mac, char *s_ip, char *d_mac, char *d_ip, short oper, int offset, char *frame) {
	arp_t arp;
	arp.htype = ARP_HTYPE_ETHERNET;
	arp.ptype = ETYPE_IP;
	arp.hlen = 6;
	arp.plen = 4;
	arp.oper = oper;
	parse_mac_string(s_mac, arp.sha);
	parse_ip_string(s_ip, arp.spa);
	parse_mac_string(d_mac, arp.tha);
	parse_ip_string(d_ip, arp.tpa);
	
	return build_arp(&arp, offset, frame);
}
