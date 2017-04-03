#ifndef _PALLOC_H
#define _PALLOC_H

/* Determine the number of bins according to the bits required for
+   each component of the address*/
#  define MAX_PALLOC_BITS 8
#  define MAX_PALLOC_BINS (1 << MAX_PALLOC_BITS)
#  define COLOR_BITMAP(name) DECLARE_BITMAP(name, MAX_PALLOC_BINS)



int set_palloc_mask(unsigned long mask);

int page_to_color(unsigned long paddr);

int set_mc_xor(int mode);

int set_palloc_ctrl(int bit, int xor_bit);
#endif
