#include "atomic.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

typedef struct st{
	int num;
	ATOMICQ_ENTRY(st) next;
}st;
ATOMICQ_HEAD(,st) head;

void *atomic_task(void *arg)
{
	st lh, *stp;
	int nb  = *(int *)arg;

	lh.num = nb;
	
	while(1)
	{
		stp = &lh;
		ATOMICQ_PUT(&head, stp, next);
		sleep(1);
		ATOMICQ_GET(&head, stp, next);
		if (stp != NULL){
			printf("nb:%d\tstp: %d\n", nb, stp->num);
		}
	}
}

void main(void)
{
	st zy, *sp;
	
	pthread_t th1, th2, th3;
	int nb1=1, nb2=2, nb3=3;
	int ret = 0;

	ATOMICQ_INIT(&head);
	zy.num = 7;
	sp = &zy;
	/* put sp into head */
	ATOMICQ_PUT(&head, sp, next);

	sp = NULL;
	/* get sp from head */
	ATOMICQ_GET(&head, sp, next);

	printf("st : %d\n", sp->num);
	ATOMICQ_PUT(&head, sp, next);

	/* create thread 1 & 2 */
	ret = pthread_create(&th1, NULL, atomic_task, &nb1); 
	if (ret != 0)
	{
		printf("create thread 1 fail!\n");
	}

	ret = pthread_create(&th2, NULL, atomic_task, &nb2); 
	if (ret != 0)
	{
		printf("create thread 2 fail!\n");
	}
	
	ret = pthread_create(&th3, NULL, atomic_task, &nb3); 
	if (ret != 0)
	{
		printf("create thread 2 fail!\n");
	}
	while(1)
	{
		sleep(1);
	}
}
