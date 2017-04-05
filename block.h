#ifndef _BLOCK_H
#define _BLOCK_H

#include "list.h"

#define BLOCK_COLOR_BIN	(16)

#define MEM_SIZE	0x1000000
#define PAGE_SHIFT	12
#define PAGE_SIZE	(1<<PAGE_SHIFT)

typedef struct page_buf
{
	struct list_head	list;
	char buf[PAGE_SIZE - sizeof(struct list_head)];
}t_page_buf;

typedef struct mem_info
{
	void *start_addr;
	unsigned int size;
	unsigned int free_count;
	t_page_buf	*page;
	struct list_head	color_list[BLOCK_COLOR_BIN];
}t_mem_info;

void malloc_init(void);
t_page_buf * malloc_page(int color);
void free_page(void *addr);
#endif
