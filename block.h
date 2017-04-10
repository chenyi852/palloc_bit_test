#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "atomic.h"
#include "list.h"

#define BLOCK_COLOR_BIN	(16)

#define MEM_SIZE	0x1000000
#define PAGE_SHIFT	12
#define PAGE_SIZE	(1<<PAGE_SHIFT)
#define NR_CPUS		(4)

typedef struct page_buf
{
	struct list_head	list;
	ATOMICQ_ENTRY(page_buf) next;
	char buf[PAGE_SIZE - sizeof(struct list_head)];	
}page_buf;

typedef struct cpu_cache{
	ATOMICQ_ENTRY(cpu_cache)	next;
}cpu_cache;

typedef struct mem_info
{
	void *start_addr;
	unsigned int size;
	unsigned int free_count;
	page_buf	*page;
	struct list_head	color_list[BLOCK_COLOR_BIN];
	ATOMICQ_HEAD(,page_buf)	cpuq[NR_CPUS];
	cpu_cache cache[NR_CPUS];
}t_mem_info;

void malloc_init(void);
page_buf * malloc_page(int color);
void free_page(void *addr);
#endif /* _BLOCK_H_ */
