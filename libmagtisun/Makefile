LIB = -lcurl
CFLAGS = -g -O2 -Wall -fPIC
OBJS = libmagtisun.o

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIB)

libmagtisun.a: $(OBJS)
	$(AR) rcs libmagtisun.a $(OBJS)
	@echo [-] Syncing static library
	sync

libmagtisun.o: libmagtisun.h

.PHONY: clean
clean:
	$(RM) libmagtisun.a $(OBJS)
