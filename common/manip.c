#include <string.h>
#include <stdlib.h>
#include "manip.h"

int parse_mac_string(const char *mac, char *out) {
	long b;
	int i;
	for (i = 0; i < 6; ++i) {
		b = strtol(mac+(3*i), (char **) NULL, 16);
		out[i] = (char)b;
	}

	return 1;
}

int parse_ip_string(const char *ip, char *out) {
	char *sep = ".";
	char *octet;
	long b;
	int i;
	char *cp;

	cp = strdup(ip);
	for(i = 0, octet = strsep(&cp, sep); octet; octet = strsep(&cp, sep), ++i) {
		b = strtol(octet, (char **) NULL, 10);
		out[i] = (char)b;
	}
	free(cp);

	return 1;
}
