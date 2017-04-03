#ifndef _BIT_OPTS_H
#define _BIT_OPTS_H

#define BITS_PER_LONG (sizeof(long)*8)

#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) & (BITS_PER_LONG - 1)))
#define BITMAP_LAST_WORD_MASK(nbits) (~0UL >> (-(nbits) & (BITS_PER_LONG - 1)))

/*
 *  * This looks more complex than it should be. But we need to
 *   * get the type for the ~ right in round_down (it needs to be
 *    * as wide as the result!), and we want to evaluate the macro
 *     * arguments just once each.
 *      */
#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

/*
 *  * min()/max()/clamp() macros that also do
 *   * strict type-checking.. See the
 *    * "unnecessary" pointer comparison.
 *     */
#define min(x, y) ({				\
			typeof(x) _min1 = (x);			\
			typeof(y) _min2 = (y);			\
			(void) (&_min1 == &_min2);		\
			_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
			typeof(x) _max1 = (x);			\
			typeof(y) _max2 = (y);			\
			(void) (&_max1 == &_max2);		\
			_max1 > _max2 ? _max1 : _max2; })


#define for_each_set_bit(bit, addr, size) \
	for ((bit) = find_first_bit((addr), (size));		\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))





#endif
