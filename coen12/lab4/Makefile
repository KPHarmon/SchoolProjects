CC	= gcc
CFLAGS	= -g -Wall
PROGS	= maze radix unique parity

.PHONY: all
all:	$(PROGS)

clean:
	$(RM) $(PROGS) *.o core
.PHONY: clean

maze:	maze.o list.o
	$(CC) $(CFLAGS) -o maze maze.o list.o -lcurses
.PHONY: maze

radix:	radix.o list.o
	$(CC) $(CFLAGS) -o radix radix.o list.o -lm
.PHONY: radix

unique:	unique.o set.o list.o
	$(CC) $(CFLAGS) -o unique unique.o set.o list.o
.PHONY: unique

parity:	parity.o set.o list.o
	$(CC) $(CFLAGS) -o parity parity.o set.o list.o
.PHONY: parity

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
