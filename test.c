#include <stdio.h>
#include <stdint.h>
#include "palloc.h"
#include "block.h"
#include "bitops.h"


static int mc_xor_bits[64] = {0};



static void palloc_test(void)
{
	malloc_init();
	
	set_mc_xor(1);
	set_palloc_mask(0x1E000);
	set_palloc_ctrl(13, 17);
	set_palloc_ctrl(14, 18);
	set_palloc_ctrl(15, 19);
	set_palloc_ctrl(16, 20);

	page_to_color(0x21000);
	page_to_color(0x4000);

	
}

void test_xor(void)
{
	int i = 0;
	
	for(i = 0; i < 10; i ++)
	{
		printf("%d ^ 0 = %d\n", i, i^0);
	}
	
	for(i = 0; i < 10; i ++)
	{
		printf("%d ^ 1 = %d\n", i, i^1);
	}
}

void main(void)
{
	int val = 0;
	int i = 0;
	uint64_t addr = 0x12345678;

	mc_xor_bits[12] = 17;	

	mc_xor_bits[13] = 18;
	
	test_xor();

	for (i = 0; i < sizeof(mc_xor_bits); i++)
	{
		if (mc_xor_bits[i] == 0)
			continue;
	
		val = ((addr >> i) & 0x1) ^ ((addr>>mc_xor_bits[i] >> i) & 0x1);

		printf(" %d ^ %d =  %d\n", i, mc_xor_bits[i], val);
	}

	printf("-------begain palloc test!----------------\n");
	palloc_test();
}
