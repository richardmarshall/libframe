#include <pcap.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"

int main()
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *inject_int_desc = NULL;
	icmp_t *icmp = NULL;
	struct pdu *icmp_pdu = NULL;
	struct frame *frame = NULL;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	int i, count = 100;

	/* create frame */
	if (!(frame = create_frame(1500))) {
		exit(1);
	}
	
	/* Create icmp packet exit on failure */	
	if (!(icmp_pdu = icmp_create(frame, ICMP_ECHO_REQUEST, ICMP_NOCODE,
							0xef68, 1, 56))) {
		free_frame(&frame);
		exit(2);
	}
	icmp = icmp_pdu->data;

	/* Create ip packet exit on failure */	
	if (!ipv4_simple_create(frame, 0, 0, DF, 0, 64, 1, src_ip, dst_ip)) {
		free_frame(&frame);
		exit(3);
	}
	
	/* Create ether header, exit on failure */
	if (!etherii_simple_create(frame, dst_mac, src_mac, ETYPE_IP)) {
		free_frame(&frame);
		exit(4);
	}

	/* open interface for injection via libpcap */
	if ((inject_int_desc = pcap_open_live("br0", BUFSIZ, 1, -1, errbuf)) == NULL) {
		printf ("\nError: %s\n", errbuf );
		free_frame(&frame);
		exit(5);
	}

	/* do actual injection */
	for (i = 0; i < count; ++i) {
		pcap_inject(inject_int_desc, frame->payload, frame->size);
		icmp->sequence = htons(ntohs(icmp->sequence)+1);
		icmp->checksum = 0;
		icmp->checksum = rfc1071_checksum(icmp, sizeof(icmp_t)+56);
	}
	pcap_close(inject_int_desc);
	
	free_frame(&frame);
	exit(0);

}
