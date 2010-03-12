CC=gcc
CFLAGS=-I./include -Wall -g
AR=ar
RM=rm -f
LIBPACKET=libframe.a
OBJS=l3/arp.o l2/etherii.o common/manip.o common/pdu.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

libframe.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

inject: libframe.a inject.o
	$(CC) $(CFLAGS) inject.c -o inject -L. -lframe -lpcap

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBPACKET)
	$(RM) inject.o inject
