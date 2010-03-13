CC=gcc
CFLAGS=-I../include -Wall -g
RM=rm -f

arp_example: 
	$(CC) $(CFLAGS) arp_example.c -o arp_example -L.. -lframe -lpcap
pvst_example: 
	$(CC) $(CFLAGS) pvst_example.c -o pvst_example -L.. -lframe -lpcap


clean:
	$(RM) *.o
