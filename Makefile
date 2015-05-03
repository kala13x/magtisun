LIB = -lcurl
OBJ = o
CFLAGS = -g -O2 -Wall

OBJS = magtisun.$(OBJ) libmagtisun.$(OBJ) info.$(OBJ) slog.$(OBJ)

all: $(OBJS)
	$(CC) $(CFLAGS) -o magtisun $(OBJS) $(LIB)

magtisun.$(OBJ): libmagtisun.h info.h slog.h stdinc.h
libmagtisun.$(OBJ): libmagtisun.h stdinc.h
info.$(OBJ): info.h stdinc.h
slog.$(OBJ): slog.h stdinc.h

.PHONY: clean

clean:
	$(RM) magtisun $(OBJS)
