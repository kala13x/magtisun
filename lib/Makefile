LIB = -lcurl
CFLAGS = -g -O2 -Wall
OBJS = magtisun.o

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIB)

libmagtisun.a: $(OBJS)
	$(AR) rcs libmagtisun.a $(OBJS)
	@echo [-] Syncing static library
	sync

magtisun.o: magtisun.h

.PHONY: clean
clean:
	$(RM) libmagtisun.a $(OBJS)
