#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include "etypes.h"
#include "manip.h"
#include "etherii.h"
#include "arp.h"

#define FRAME_SIZE 1500

int main(int argc, char **argv) {

	char errbuf[ PCAP_ERRBUF_SIZE ];
	pcap_t *inject_int_desc;
	char packet_data[FRAME_SIZE];
	int i;
	int len = 0;

	char *src_mac = "00:01:02:03:04:05";
	char *dst_mac = "ff:ff:ff:ff:ff:ff";
	char *src_ip = "208.96.55.76";
	char *dst_ip = "208.96.55.77";
	int etype = ETYPE_ARP;

	len = set_etherii_header(dst_mac, src_mac, etype, packet_data);
	len = set_arp(src_mac, src_ip, dst_mac, dst_ip, ARP_OPER_QUERY, len, packet_data);

	if (( inject_int_desc = pcap_open_live ( "eth0", BUFSIZ, 1, -1, errbuf ) ) == NULL )
	{
		printf ("\nError: %s\n", errbuf );
		exit(1);
	}

	for(i = 0; i < 100; ++i) {
		pcap_inject( inject_int_desc, packet_data, len);
	}
	pcap_close( inject_int_desc );

	exit(0);

}
