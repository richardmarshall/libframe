#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"

int main() {
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *inject_int_desc;
	struct frame *frame = NULL;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	uint16_t etype_dot1q = ETYPE_ARP;
	uint16_t etype = ETYPE_DOT1Q;
	uint16_t oper = ARP_OPER_QUERY;
	uint16_t pcp = 7;
	uint16_t cfi = 1;
	uint16_t vid = 1;
	int i, count = 100;

	/* craete frame */
	if (!(frame = create_frame(1500))) {
		exit(1);
	}

	/* Create arp packet exit on failure */	
	if (!arp_ie_simple_create(frame, oper, src_mac, src_ip, dst_mac, dst_ip)) {
		free_frame(&frame);
		exit(1);
	}
	
	/* Create dot1q tag exit on failure */	
	if (!dot1q_create(frame, pcp, cfi, vid, etype_dot1q)) {
		free_frame(&frame);
		exit(1);
	}

	/* Create ether header, free arp packet and exit on failure */
	if (!etherii_simple_create(frame, dst_mac, src_mac, etype)) {
		free_frame(&frame);
		exit(2);
	}

	/* open interface for injection via libpcap */
	if ((inject_int_desc = pcap_open_live( "br0", BUFSIZ, 1, -1, errbuf)) == NULL) {
		printf ("\nError: %s\n", errbuf );
		exit(1);
	}

	/* do actual injection */
	for(i = 0; i < count; ++i) {
		pcap_inject( inject_int_desc, frame->payload, frame->size);
	}
	pcap_close( inject_int_desc );

	free_frame(&frame);

	exit(0);

}
