LIB = -lcurl
CFLAGS = -g -O2 -Wall -fPIC
OBJS = magtisun.o

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIB)

magtisun.a: $(OBJS)
	$(AR) rcs magtisun.a $(OBJS)
	@echo [-] Syncing static library
	sync

magtisun.o: magtisun.h

.PHONY: clean
clean:
	$(RM) magtisun.a $(OBJS)
