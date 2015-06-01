CFLAGS = -g -O2 -Wall -Ilibmagtisun -Ilibslog
LIB = -lcurl libmagtisun/libmagtisun.a libslog/slog.a
PREFIX = /usr/local

OBJS = magtisun.o info.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o magtisun $(OBJS) $(LIB)

magtisun.o: info.h stdinc.h
info.o: info.h stdinc.h

.PHONY: install
install: magtisun
	install -m 0755 magtisun $(PREFIX)/bin

.PHONY: clean
clean:
	$(RM) magtisun $(OBJS)
