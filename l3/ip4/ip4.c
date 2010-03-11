
struct ip {
	short ver_hlen_ds;
	short tlen;
	short ident;
	short flags_fragoff;
	char ttl;
	char protocol;
	short checksum;
	int saddr;
	int daddr;
} __attribute__((__packed__));
typedef struct ip ip_t;

int build_ip(ip_t *ip, int offset, char *frame) {
	memcpy((void *)(frame+offset), (void *)ip, sizeof(ip_t));
	return offset+sizeof(ip_t);
}

int get_ip_field(int field, arp_t *arp) {

}

void set_ip_field(int field, int value, arp_t *arp) {

}
