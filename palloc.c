#include <stdio.h>
#include "bitops.h"

#define DEBUG 1 

#ifdef	DEBUG 
#define DBG(fmt, ...)	\
	printf(fmt, ##__VA_ARGS__)
#else
#define DBG
#endif

static unsigned long sysctl_palloc_mask = 0x0;
static int mc_xor_bits[64];
static int use_mc_xor = 0;

int palloc_bins(void)
{
	return min((1 << bitmap_weight(&sysctl_palloc_mask, 8*sizeof (unsigned long))),
		   MAX_PALLOC_BINS);
}

int set_palloc_mask(unsigned long mask)
{
	sysctl_palloc_mask = mask;
	DBG("mask is set to 0x%llx\n", sysctl_palloc_mask);
	return 0;
}

int set_mc_xor(int mode)
{
	use_mc_xor = mode;
	
	return 0;
}

int set_palloc_ctrl(int bit, int xor_bit)
{
	mc_xor_bits[bit] = xor_bit;

	return 0;
}


int page_to_color(unsigned long paddr)
{
	int color = 0;
	int idx = 0;
	int c;

	for_each_set_bit(c, &sysctl_palloc_mask, sizeof(unsigned long) * 8) {
		if (use_mc_xor) {
			if (((paddr >> c) & 0x1) ^ ((paddr >> mc_xor_bits[c]) & 0x1))
				color |= (1 << idx);
		} else {
			if ((paddr >> c) & 0x1)
				color |= (1 << idx);
		}
		DBG("mask %llx\t bit is %d, idx:%d color : %d\n", sysctl_palloc_mask,  c, idx, color);
		idx++;
	}

	return color;
}
