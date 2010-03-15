#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"


int main() {
	char errbuf[ PCAP_ERRBUF_SIZE ];
	pcap_t *inject_int_desc;
	header_t *ether_header;
	pdu_t *ether_frame = NULL;
	pdu_t *stp_pdu, *llc_pdu;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "00:02:03:04:05:06";
	int i, count = 100;

	/* Create RSTP packet exit on failure */
	stp_pdu = stp_rstp_simple_create( 0x7c, 32768, src_mac, 0, 32768, src_mac, 0x8014, 0, 20, 2, 15, 0 );

	/* Create LLC PDU */
	llc_pdu = ether8022llc_quick_create( SAP_BPDU, SAP_BPDU, CFIELD_UNNUMBERED_INFO | CFIELD_UNNUMBERED_FRAME, stp_pdu);

	/* Create 802.3 header */
	ether_header = ether8023_simple_header_create( dst_mac, src_mac, llc_pdu->size );

	/* Create 802.3 frame */
	ether_frame = pdu_create( ether_header, llc_pdu );

	/* open interface for injection via libpcap */
	if (( inject_int_desc = pcap_open_live ( "wlan0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
	{
		printf ("\nError: %s\n", errbuf );
		exit(1);
	}

	/* do actual injection */
	for(i = 0; i < count; ++i) {
		pcap_inject( inject_int_desc, ether_frame->data, ether_frame->size);
	}
	pcap_close( inject_int_desc );

	free_pdu(&ether_frame);

	exit(0);

}
