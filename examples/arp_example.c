#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"

int main() {
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *inject_int_desc = NULL;
	struct frame *frame = NULL;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	uint16_t etype = ETYPE_ARP;
	uint16_t oper = ARP_OPER_QUERY;
	int i, count = 100;

	/* create frame */
	if (!(frame = create_frame(1500))) {
		exit(1);
	}

	/* Create arp packet exit on failure */	
	if (!arp_ie_simple_create(frame, oper, src_mac, src_ip, dst_mac, dst_ip)) {
		free_frame(&frame);
		exit(2);
	}
	
	/* Create ether header, exit on failure */
	if (!etherii_simple_create(frame, dst_mac, src_mac, etype)) {
		free_frame(&frame);
		exit(3);
	}

	/* open interface for injection via libpcap */
	if ((inject_int_desc = pcap_open_live("br0", BUFSIZ, 1, -1, errbuf)) == NULL)
	{
		printf ("\nError: %s\n", errbuf );
		free_frame(&frame);
		exit(1);
	}

	/* do actual injection */
	for (i = 0; i < count; ++i) {
		pcap_inject(inject_int_desc, frame->payload, frame->size);
	}
	pcap_close(inject_int_desc);
	
	free_frame(&frame);
	exit(0);

}
