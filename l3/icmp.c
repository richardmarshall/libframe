#include <stdio.h>
#include <arpa/inet.h>
#include <icmp.h>
#include <checksum.h>
#include <protos.h>

struct pdu *icmp_create(struct frame *fp, uint8_t type, uint8_t code, 
			uint16_t id, uint16_t sequence, size_t padlen)
{
	struct pdu *pdu = NULL;
	icmp_t *icmp = NULL;
	uint8_t *padding = NULL;
	int i;

	if ((pdu = create_pdu(fp, sizeof(icmp_t)+padlen, PROTO_ICMP))) {
		icmp = pdu->data;
		padding = ((uint8_t *)icmp) + sizeof(icmp_t);
		icmp->type = type;
		icmp->code = code;
		icmp->id = htons(id);
		icmp->sequence = htons(sequence);
		for(i = 0; i < padlen; ++i)
			padding[i] = i;
		icmp->checksum = 0;
		icmp->checksum = rfc1071_checksum((void *)icmp, sizeof(icmp_t)+padlen);
	}

	return pdu;
}
