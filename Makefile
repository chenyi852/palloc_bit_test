
CC=gcc
CFLAGS=-g

OBJS=  bitops.o palloc.o
DEPS = bitops.h palloc.h

%.o: %.c $(DEPS)
	$(CC) -c  $(CFLAGS) -o $@ $<

test : test.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
		rm -f *.o test
