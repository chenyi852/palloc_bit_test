
CC=gcc
CFLAGS=-g -std=gnu99

OBJS=  bitops.o palloc.o block.o
DEPS = bitops.h palloc.h block.h atomic.h

%.o: %.c $(DEPS)
	$(CC) -c  $(CFLAGS) -o $@ $<

test : test.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

atomic:atomic_test.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
		rm -f *.o test
