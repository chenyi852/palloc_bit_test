/*
 * chenyi
 * chenyi852@gmail.com
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdint.h>

#include "palloc.h"
#include "list.h"
#include "bitops.h"
#include "block.h"


static void *memchunk;

static t_mem_info  globe_mem_info;
void malloc_init(void)
{
	t_mem_info	*mem_info_ptr = &globe_mem_info;
	int i;
	
	memchunk = memalign(1<<12, MEM_SIZE);
	mem_info_ptr->start_addr	= memchunk;
	mem_info_ptr->size			= MEM_SIZE;
	mem_info_ptr->free_count	= (mem_info_ptr->size / PAGE_SIZE);
	mem_info_ptr->page			= (t_page_buf *)mem_info_ptr->start_addr;	
	
	for (i = 0; i < BLOCK_COLOR_BIN; i++)
	{
		INIT_LIST_HEAD(&mem_info_ptr->color_list[i]);
	}
	
	*(int *)memchunk = 0x5a5a;
		
	printf("%p =  0x%x\n", memchunk, *(unsigned int *)memchunk);
}


t_page_buf * malloc_page(int color)
{
	t_mem_info	*mem_info_ptr = &globe_mem_info;
	t_page_buf	*page;
	struct list_head *t;
	int page_color = 0;
	t_page_buf	*color_page = NULL;
	
	/* first get page from page pool, then get page from palloc */
	while (mem_info_ptr->free_count > 0){
		/* need aomic operation? */
		page = mem_info_ptr->page;
		page_color = page_to_color(page);
		
		PDBG("----%p!!!!====, %d/%d\n", page, color, page_color);
		
		mem_info_ptr->page++;
		mem_info_ptr->free_count--;
		if (page_color == color){
			PDBG("allocate from pool %p\n", page);
			return page;
		}
		else {
			list_add(&page->list, &mem_info_ptr->color_list[page_color]);
		}
		
		
	}
	
	if (!list_empty(&mem_info_ptr->color_list[color])){
		color_page = list_first_entry(&mem_info_ptr->color_list[color], t_page_buf, list);	
		list_del(&color_page->list);
	}
	printf("allocate from palloc %p\n", color_page);
	return color_page;
}

void free_page(void *addr)
{
	t_mem_info	*mem_info_ptr = &globe_mem_info;
	t_page_buf	*page = (t_page_buf *)addr;
	int page_color = 0;
	
	page_color = page_to_color(addr);
		
		
	list_add(&page->list, &mem_info_ptr->color_list[page_color]);

}



