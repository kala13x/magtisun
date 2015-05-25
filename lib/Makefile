LIB = -lcurl
CFLAGS = -g -O2 -Wall -fPIC
OBJS = libmagtisun.o

all: $(OBJS)
	$(CC) -shared -o libmagtisun.so $(LIB) $(OBJS)

libmagtisun.o: libmagtisun.h

.PHONY: clean
clean:
	$(RM) libmagtisun.so $(OBJS)
