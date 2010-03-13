#ifndef __MANIPH__
#define __MANIPH__

#include <stdint.h>

int parse_mac_string(const char *mac, uint8_t *out);

int parse_ip_string(const char *ip, uint8_t *out);

#endif
