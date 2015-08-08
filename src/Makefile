CFLAGS = -g -O2 -Wall -I../lib -I../slog -Wno-unused-result
LIB = ../lib/libmagtisun.a ../slog/libslog.a -lcurl 
PREFIX = /usr/local
BINDIR = ../bin

OBJ = magtisun.o info.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o magtisun $(OBJ) $(LIB)
	@test -d $(BINDIR) || mkdir $(BINDIR)
	@install -m 0755 magtisun $(BINDIR)/
	@echo [-] Executable files builded in - $(BINDIR) folder

magtisun.o: info.h stdinc.h
info.o: info.h stdinc.h

.PHONY: install
install: magtisun
	@install -m 0755 magtisun $(PREFIX)/bin

.PHONY: clean
clean:
	$(RM) magtisun $(OBJ)
