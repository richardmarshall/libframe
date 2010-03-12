#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "frame.h"

int main() {
	char errbuf[ PCAP_ERRBUF_SIZE ];
	pcap_t *inject_int_desc;
	header_t *ether_header = NULL;
	pdu_t *ether_frame = NULL;
	pdu_t *arp_packet = NULL;
	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	uint16_t etype = ETYPE_ARP;
	uint16_t oper = ARP_OPER_QUERY;
	int i;

	arp_packet = arp_ie_simple_create( oper, src_mac, src_ip, dst_mac, dst_ip );
	ether_header = etherii_simple_header_create( dst_mac, src_mac, etype );
	ether_frame = pdu_create( ether_header, arp_packet );
	free(arp_packet);
	free(ether_header);

	if (( inject_int_desc = pcap_open_live ( "wlan0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
	{
		printf ("\nError: %s\n", errbuf );
		exit(1);
	}

	for(i = 0; i < 100; ++i) {
		pcap_inject( inject_int_desc, ether_frame->data, ether_frame->size);
	}
	pcap_close( inject_int_desc );

	free(ether_frame);

	exit(0);

}
