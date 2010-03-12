#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include "etypes.h"
#include "pdu.h"
#include "manip.h"
#include "etherii.h"
#include "arp.h"

int main(int argc, char **argv) {

	char errbuf[ PCAP_ERRBUF_SIZE ];
	pcap_t *inject_int_desc;
	int i;

	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	int etype = ETYPE_ARP;

	pdu_t layer_2_frame, layer_3_packet, layer_4_segment;

	/* open interface for injection */
	if (( inject_int_desc = pcap_open_live ( "wlan0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
	{
		printf ("\nError: %s\n", errbuf );
		exit(1);
	}

	/* tcp/ip/etherii example */

	/* create layer 4 segment */
	char *layer_4_segment = simple_tcp(sport, dport, flags, seq, payload);
	/* create layer 3 packet */
	char *layer_3_segment = simple_ip(src_ip, dst_ip, flags, layer_4_segment);
	/* create layer 2 frame */
	char *layer_2_frame = simple_etherii(dst_mac, src_mac, etype, layer_3_packet);

	/* inject 100 duplicate frames */
	for(i = 0; i < 100; ++i) {
		pcap_inject( inject_int_desc, layer_2_frame, layer_2_size);
	}
	free(layer_4_packet);
	free(layer_3_packet);
	free(layer_2_frame);

	/* arp/etherii example */

	/* create layer 3 packet */
	char *layer_3_packet = simple_arp(src_mac, src_ip, dst_mac, dst_ip, ARP_OPER_QUERY, &layer_3_size);

	/* create layer 2 frame encapsulating the layer 2 packet */
	char *layer_2_frame = simple_etherii(dst_mac, src_mac, etype, layer_3_packet, layer_3_size, &layer_2_size);

	/* inject 100 duplicate frames */
	for(i = 0; i < 100; ++i) {
		pcap_inject( inject_int_desc, layer_2_frame, layer_2_size);
	}
	free(layer_3_packet);
	free(layer_2_frame);

	pcap_close( inject_int_desc );

	exit(0);
}
