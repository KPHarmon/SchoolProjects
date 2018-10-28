CC	= gcc
CFLAGS	= -g -Wall
PROGS	= app2

.PHONY: all
all:	$(PROGS)

clean:
		$(RM) $(PROGS) *.o core
.PHONY: clean

app2:	college.o dataset.o
		$(CC) $(CFLAGS) -o college college.o dataset.o 
.PHONY: app2

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@
