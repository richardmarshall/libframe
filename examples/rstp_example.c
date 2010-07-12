#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"


int main() {
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *inject_int_desc;
	struct frame *frame;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "00:02:03:04:05:06";
	int i, count = 100;

	/* create frame */
	if (!(frame = create_frame(1500))) {
		exit(1);
	}

	/* Create RSTP packet exit on failure */
	if(!stp_rstp_simple_create(frame, 0x7c, 32768, src_mac, 0, 32768, src_mac, 0x8014, 
					0, 20, 2, 15, 0)) {
		free_frame(&frame);
		exit(2);
	}

	/* Create LLC PDU */
	if(!ether8022llc_create(frame, SAP_BPDU, SAP_BPDU, 
			CFIELD_UNNUMBERED_INFO | CFIELD_UNNUMBERED_FRAME)) {
		free_frame(&frame);
		exit(3);
	}

	/* Create 802.3 header */
	if(!ether8023_simple_create(frame, dst_mac, src_mac)) {
		free_frame(&frame);
		exit(4);
	}

	/* open interface for injection via libpcap */
	if ((inject_int_desc = pcap_open_live("br0", BUFSIZ, 1, -1, errbuf)) == NULL) {
		printf ("\nError: %s\n", errbuf );
		exit(5);
	}

	/* do actual injection */
	for(i = 0; i < count; ++i) {
		pcap_inject(inject_int_desc, frame->payload, frame->size);
	}
	pcap_close(inject_int_desc);

	free_frame(&frame);

	exit(0);

}
