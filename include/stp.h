#ifndef __STPH__
#define __STPH__

#include <stdint.h>
#include <pdu.h>
#include <protos.h>

/* STP Protocol Identifiers */
#define STP_PID_STP 0

/* STP Versions */
#define STP_VER_RSTP 2

/* STP BPDU Types */
#define STP_BPDU_RSTP 2
#define STP_BPDU_MST 2

/* STP BPDU Flags */
#define STP_BDPU_FROLE_0 0 /* unknown */
#define STP_BDPU_FROLE_1 1 /* unknown */
#define STP_BDPU_FROLE_2 2 /* unknown */
#define STP_BDPU_FROLE_DESIG 3

union stp_bpdu_flags {
	uint8_t flags;
	struct {
		uint8_t top_cng_ack : 1;
		uint8_t agreement   : 1;
		uint8_t learning    : 1;
		uint8_t port_role   : 2;
		uint8_t proposal    : 1;
		uint8_t top_change  : 1;
	};
};
typedef union stp_bpdu_flags stp_bpdu_flags_t;

/* RSTP BPDU */
struct stp_bpdu_header {
	uint16_t pid;
	uint8_t  version;
	uint8_t  type;
	stp_bpdu_flags_t flags;
	uint16_t root_pri;
	uint8_t  root_id[6];
	uint32_t root_cost;
	uint16_t bridge_pri;
	uint8_t  bridge_id[6];
	uint16_t port_id;
	uint16_t age;
	uint16_t max_age;
	uint16_t hello_time;
	uint16_t forward_delay;
	uint8_t  length;
}__attribute__((__packed__));
typedef struct stp_bpdu_header stp_bpdu_header_t;

extern struct pdu *stp_rstp_header_create(struct frame *framep, uint8_t flags, uint16_t root_pri,
					uint8_t *root_id, uint8_t root_cost,
					uint16_t bridge_pri, uint8_t *bridge_id,
					uint16_t port_id, uint16_t age,
					uint16_t max_age, uint16_t hello_time,
					uint16_t forward_delay, uint8_t len);

extern struct pdu *stp_rstp_simple_create(struct frame *framep, uint8_t flags, uint16_t root_pri,
				     char *root_id, uint8_t root_cost,
				     uint16_t bridge_pri, char *bridge_id,
				     uint16_t port_id, uint16_t age,
				     uint16_t max_age, uint16_t hello_time,
				     uint16_t forward_delay, uint8_t len);

#endif
