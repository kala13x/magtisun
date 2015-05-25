LIB = -lcurl libmagtisun/libmagtisun.so libslog/slog.so
CFLAGS = -g -O2 -Wall -Ilibmagtisun -Ilibslog
PREFIX = /usr/local

OBJS = magtisun.o info.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o magtisun  $(LIB) $(OBJS)

magtisun.o: info.h stdinc.h
info.o: info.h stdinc.h

.PHONY: install
install: magtisun
	install -m 0755 magtisun $(PREFIX)/bin

.PHONY: clean
clean:
	$(RM) magtisun $(OBJS)
