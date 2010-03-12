CC=gcc
CFLAGS=-I./include -Wall -g
AR=ar
RM=rm -f
LIBPACKET=libpacket.a
OBJS=l3/arp/arp.o l2/etherii/etherii.o common/manip.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

libpacket.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

inject: libpacket.a inject.o
	$(CC) $(CFLAGS) inject.c -o inject -L. -lpacket -lpcap

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBPACKET)
	$(RM) inject.o inject
