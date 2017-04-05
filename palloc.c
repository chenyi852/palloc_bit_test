#include <stdio.h>
#include "bitops.h"



static unsigned long sysctl_palloc_mask = 0x0;
static int mc_xor_bits[64];
static int use_mc_xor = 0;



int set_palloc_mask(unsigned long mask)
{
	sysctl_palloc_mask = mask;
	PDBG("mask is set to 0x%lx\n", sysctl_palloc_mask);
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


int page_to_color(void *paddr)
{
	int color = 0;
	int idx = 0;
	int c;
	unsigned long addr = (unsigned long)paddr;

	PDBG("[%s]paddr = 0x%016lx\n", __func__, addr);
	for_each_set_bit(c, &sysctl_palloc_mask, sizeof(unsigned long) * 8) {
		if (use_mc_xor) {
			if (((addr >> c) & 0x1) ^ ((addr >> mc_xor_bits[c]) & 0x1))
				color |= (1 << idx);
		} else {
			if ((addr >> c) & 0x1)
				color |= (1 << idx);
		}
		PDBG("mask %llx\t bit is %d, idx:%d color : %d\n", sysctl_palloc_mask,  c, idx, color);
		idx++;
	}

	return color;
}
