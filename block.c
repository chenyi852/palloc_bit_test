#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdint.h>

#define BLOCK_COLOR_BIN	(16)

#define MEM_SIZE	0x1000000
#define PAGE_SHIFT	12
#define PAGE_SIZE	(1<<PAGE_SHIFT)

static void *memchunk;

typedef struct page_buf
{
	char buf[PAGE_SIZE];
}t_page_buf;

typedef struct mem_info
{
	void *start_addr;
	unsigned int size;
	unsigned int page_count;
	t_page_buf	*page;
	void *buff[BLOCK_COLOR_BIN];
}t_mem_info;

static t_mem_info  globe_mem_info;
void malloc_init(void)
{
	t_mem_info	*mem_info_ptr = &globe_mem_info;

	
	memchunk = memalign(1<<12, MEM_SIZE);
	mem_info_ptr->start_addr	= memchunk;
	mem_info_ptr->size			= MEM_SIZE;
	mem_info_ptr->page_count	= (mem_info_ptr->size / PAGE_SIZE);
	mem_info_ptr->page			= (t_page_buf *)mem_info_ptr->start_addr;	
		
	*(int *)memchunk = 0x5a5a;
		
	printf("%p =  0x%x\n", memchunk, *(unsigned int *)memchunk);
}


void * malloc_page(int color)
{
	

}



