CC=gcc
CFLAGS=-I./include -Wall -g -std=gnu99
AR=ar
RM=rm -f
LIBFRAME=libframe.a
OBJS=l3/arp.o l2/etherii.o l2/ether8022llc.o l2/ether8022snap.o l2/stp.o common/manip.o common/pdu.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

libframe.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFRAME)
	$(RM) example.o example
