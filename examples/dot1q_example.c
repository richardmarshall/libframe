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
	header_t *dot1q_tag = NULL;
	pdu_t *dot1q_frame = NULL;
	pdu_t *arp_packet = NULL;
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

	/* Create arp packet exit on failure */	
	if ( !(arp_packet = arp_ie_simple_create( oper, src_mac, src_ip, dst_mac, dst_ip )))
		exit(1);
	
	/* Create dot1q tag exit on failure */	
	if ( !(dot1q_tag = dot1q_header_create( pcp, cfi, vid, etype_dot1q)))
		exit(1);

        /* Create dot1q frame */
	if ( !(dot1q_frame = pdu_create( dot1q_tag, arp_packet ))) {

	        free_pdu(&arp_packet);
	        free_header(&dot1q_tag);
		exit(2);
		}

	/* Create ether header, free arp packet and exit on failure */
	if ( !(ether_header = etherii_simple_header_create( dst_mac, src_mac, etype ))) {
		free_pdu(&arp_packet);
		free_header(&dot1q_tag);
		free_pdu(&dot1q_frame);
		exit(2);
	}

	/* Create ether frame, exit on failure */
	if ( !(ether_frame = pdu_create( ether_header, dot1q_frame ))) {
		free_pdu(&arp_packet);
		free_header(&dot1q_tag);
		free_header(&ether_header);
		free_pdu(&dot1q_frame);
		exit(3);
	}
	free_pdu(&arp_packet);
	free_header(&dot1q_tag);
	free_header(&ether_header);

	/* open interface for injection via libpcap */
	if (( inject_int_desc = pcap_open_live ( "br0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
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
