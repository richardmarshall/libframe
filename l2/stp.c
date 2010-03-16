#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "pdu.h"
#include "stp.h"
#include "manip.h"

extern header_t *stp_rstp_header_create(uint8_t flags, uint16_t root_pri, 
					uint8_t *root_id, uint8_t root_cost, 
					uint16_t bridge_pri, uint8_t *bridge_id,
					uint16_t port_id, uint16_t age, 
					uint16_t max_age, uint16_t hello_time, 
					uint16_t forward_delay, uint8_t len)
{
	header_t *header = NULL;
	stp_bpdu_header_t *bpdu = NULL;

	/* return NULL if malloc fails */
	if (!(header = malloc(sizeof(header_t))))
		return NULL;

	/* set header size */
	header->size = sizeof(stp_bpdu_header_t);

	/* free header and return null if malloc fails */
	if(!(header->data = malloc(header->size))) {
		free(header);
		return NULL;
	}

	/* fill up the bpdu */
	bpdu = header->data;
	bpdu->pid = STP_PID_STP;
	bpdu->version = STP_VER_RSTP;
	bpdu->type = STP_BPDU_RSTP;
	bpdu->flags = (stp_bpdu_flags_t)flags;
	bpdu->root_pri = htons(root_pri);
	memcpy((void *)bpdu->root_id, (void *)root_id, 6);
	bpdu->root_cost = root_cost;
	bpdu->bridge_pri = htons(bridge_pri);
	memcpy((void *)bpdu->bridge_id, (void *)bridge_id, 6);
	bpdu->port_id = htons(port_id);
	bpdu->age = htons(age);
	bpdu->max_age = htons(age);
	bpdu->hello_time = htons(hello_time);
	bpdu->forward_delay = htons(forward_delay);
	bpdu->length = len;

	return header;
}

extern pdu_t *stp_rstp_create(uint8_t flags, uint16_t root_pri,
			      uint8_t *root_id, uint8_t root_cost,
			      uint16_t bridge_pri, uint8_t *bridge_id,
			      uint16_t port_id, uint16_t age, uint16_t max_age,
			      uint16_t hello_time, uint16_t forward_delay,
			      uint8_t len)
{
	pdu_t *pdu = NULL;
	header_t *header = NULL;

	/* create bpdu */
	header = stp_rstp_header_create(flags, root_pri, root_id, root_cost,
					bridge_pri, bridge_id, port_id, age,
					max_age, hello_time, forward_delay, 
					len);

	if (header == NULL)
		return NULL;

	pdu = pdu_create(header, NULL);
	free(header);

	return pdu;
}

extern pdu_t *stp_rstp_simple_create(uint8_t flags, uint16_t root_pri,
				     char *root_id, uint8_t root_cost,
				     uint16_t bridge_pri, char *bridge_id,
				     uint16_t port_id, uint16_t age,
				     uint16_t max_age, uint16_t hello_time,
				     uint16_t forward_delay, uint8_t len)
{
	uint8_t broot_id[6], bbridge_id[6];

	if (!parse_mac_string(root_id,broot_id)) 
		return NULL;
	if (!parse_mac_string(bridge_id,bbridge_id)) 
		return NULL;

	return stp_rstp_create(flags, root_pri, broot_id, root_cost, bridge_pri,
			       bbridge_id, port_id, age, max_age, hello_time, 
			       forward_delay, len);
}
