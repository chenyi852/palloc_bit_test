#include "atomic.h"

#include <stdio.h>

typedef struct st{
	int num;
	ATOMICQ_ENTRY(st) next;
}st;

void main(void)
{
	st zy, *sp;
	ATOMICQ_HEAD(,st) head;
	
	zy.num = 7;
	sp = &zy;
	ATOMICQ_PUT(&head, sp, next);

	sp = NULL;

	ATOMICQ_GET(&head, sp, next);

	printf("st : %d\n", sp->num);


}
