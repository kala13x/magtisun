LIB = -lcurl lib/libmagtisun.so
CFLAGS = -g -O2 -Wall -Ilib
PREFIX = /usr/local

OBJS = magtisun.o info.o slog.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o magtisun  $(LIB) $(OBJS)

magtisun.o: info.h slog.h stdinc.h
info.o: info.h stdinc.h
slog.o: slog.h

.PHONY: install
install: magtisun
	install -m 0755 magtisun $(PREFIX)/bin

.PHONY: clean
clean:
	$(RM) magtisun $(OBJS)
