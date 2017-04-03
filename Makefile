
CC=gcc
CFLAGS=-g

OBJS=  bitops.o palloc.o block.o
DEPS = bitops.h palloc.h block.h

%.o: %.c $(DEPS)
	$(CC) -c  $(CFLAGS) -o $@ $<

test : test.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
		rm -f *.o test
