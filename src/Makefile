CFLAGS = -g -O2 -Wall -I../magtisun -I../slog
LIB = -lcurl ../magtisun/magtisun.a ../slog/slog.a
PREFIX = /usr/local
BINDIR = ../bin

OBJS = magtisun.o info.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o magtisun $(OBJS) $(LIB)
	@test -d $(BINDIR) || mkdir $(BINDIR)
	@install -m 0755 magtisun $(BINDIR)/
	@install -m 0664 config.cfg $(BINDIR)
	@echo [-] Executable files builded in - $(BINDIR) folder

magtisun.o: info.h stdinc.h
info.o: info.h stdinc.h

.PHONY: install
install: magtisun
	install -m 0755 magtisun $(PREFIX)/bin

.PHONY: clean
clean:
	$(RM) magtisun $(OBJS)
