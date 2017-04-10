#include <stdio.h>
#include <stdint.h>
#include "palloc.h"
#include <pthread.h>

#include "bitops.h"
#include "list.h"
#include "block.h"



static int mc_xor_bits[64] = {0};


#define MALLOC_TIME	(100)

void *malloc_page_test(void *arg)
{
	int i  = 0;
	page_buf * page[MALLOC_TIME];

	for (i = 0; i < 100; i++)
	{
		page[i]  = malloc_page(1);
		if (page[i] == NULL){
			printf("alloc null\n");
			continue;
		}
		*(unsigned long *)page[i] = 0x5a5a5a5a;
		/* printf("%p =  0x%lx\n", page, *(unsigned long *)page); */
		//free_page(page);
	}
	
	for (i = 0; i < 100; i++)
	{
			free_page(page[i]);
	}
	
	/* second test 88888888888888888888 */
	for (i = 0; i < 100; i++)
	{
		page[i]  = malloc_page(1);
		if (page[i] == NULL){
			printf("alloc null\n");
			continue;
		}
		*(unsigned long *)page[i] = 0x5a5a5a5a;
		/* printf("%p =  0x%lx\n", page[i], *(unsigned long *)page[i]); */
		//free_page(page);
	}
	
	for (i = 0; i < 100; i++)
	{
			free_page(page[i]);
	}
}

static void palloc_test(void)
{
	pthread_t th1, th2;	
	int ret = 0;
	malloc_init();
	
	set_mc_xor(1);
	set_palloc_mask(0x1E000);
	set_palloc_ctrl(13, 17);
	set_palloc_ctrl(14, 18);
	set_palloc_ctrl(15, 19);
	set_palloc_ctrl(16, 20);

	page_to_color((void *)0x21000);
	page_to_color((void *)0x4000);

	ret = pthread_create(&th1, NULL, malloc_page_test, NULL);
	if (ret != 0){
		printf("create thread 1 fail!\n");
	}

	//ret = pthread_create(&th2, NULL, malloc_page_test, NULL);
	if (ret != 0){
		printf("create thread 2 fail!\n");
	}

	pthread_join(th1, NULL);
	//pthread_join(th2, NULL);
	printf("----finish palloc test!-------------\n");
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

typedef struct stu_num
{
	int num;
	struct list_head list;
}t_stu;
void test_list(void)
{
	static t_stu stu_head;
	t_stu	mstu, astu;
	t_stu *stu;
	
	INIT_LIST_HEAD(&stu_head.list);
	mstu.num = 1;
	list_add(&mstu.list, &stu_head.list);
	//printf("1: %lx\n", mstu.list.next);
	astu.num = 2;
	list_add(&astu.list, &stu_head.list);
	//printf("2: %lx\n", astu.list.next);
	list_for_each_entry(stu, &stu_head.list, list)
	{
		printf("stu.num =  %d\n", stu->num);
		
	}
	list_del(&mstu.list);
	list_del(&astu.list);
	
	if(list_empty(&stu_head.list))
		printf("the list is empty!\n");
	

}

void main(void)
{
	int val = 0;
	int i = 0;
	uint64_t addr = 0x12345678;

	mc_xor_bits[12] = 17;	

	mc_xor_bits[13] = 18;
	
	test_list();
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
