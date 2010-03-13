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
	pdu_t *snap_pdu, *llc_pdu;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "00:02:03:04:05:06";
	int i, count = 100;
	uint32_t ocode = 0x0c;
	
	/* Create PVST+ packet exit on failure */
	/* Will add when PVST+ protocol is added */

	/* Create SNAP PDU */
	snap_pdu = ether8022snap_quick_create( ocode, SNAP_PID_PVST, NULL );

	/* Create LLC PDU */
	llc_pdu = ether8022llc_quick_create( SAP_SNAP, SAP_SNAP, CFIELD_UNNUMBERED_INFO | CFIELD_UNNUMBERED_FRAME, snap_pdu);

	/* Create 802.3 header */
	ether_header = ether8023_simple_header_create( dst_mac, src_mac, llc_pdu->size );

	/* Create 802.3 frame */
	ether_frame = pdu_create( ether_header, llc_pdu );

	/* open interface for injection via libpcap */
	if (( inject_int_desc = pcap_open_live ( "eth0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
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
