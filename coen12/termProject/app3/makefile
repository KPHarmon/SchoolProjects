CC	= gcc
CFLAGS	= -g -Wall
PROGS	= app3

.PHONY: all
all:	$(PROGS)

clean:
		$(RM) $(PROGS) *.o core
.PHONY: clean

app3:	college.o dataset.o
		$(CC) $(CFLAGS) -o college college.o dataset.o 
.PHONY: app3

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@
