CC=gcc
CFLAGS=-I../include -Wall -g
RM=rm -f

all:
	make arp_example
	make pvst_example

arp_example: arp_example.c
	$(CC) $(CFLAGS) arp_example.c -o arp_example -L.. -lframe -lpcap
dot1q_example: dot1q_example.c
	$(CC) $(CFLAGS) dot1q_example.c -o dot1q_example -L.. -lframe -lpcap
pvst_example: pvst_example.c
	$(CC) $(CFLAGS) pvst_example.c -o pvst_example -L.. -lframe -lpcap
rstp_example: rstp_example.o
	$(CC) $(CFLAGS) rstp_example.c -o rstp_example -L.. -lframe -lpcap


clean:
	$(RM) *.o
