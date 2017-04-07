#ifndef _SYS_ATOMIC_H_
#define _SYS_ATOMIC_H_

#define xchg(a, b, c) __atomic_exchange((a), (b), (c), __ATOMIC_SEQ_CST)
#define cmpxchg(a, b, c) __atomic_compare_exchange((a), (b), (c), 0, \
		__ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define or_fetch(a, b) __atomic_or_fetch((a), (b), __ATOMIC_SEQ_CST)
#define and_fetch(a, b) __atomic_and_fetch((a), (b), __ATOMIC_SEQ_CST)
#define fetch_add(a, b) __atomic_fetch_add((a), (b), __ATOMIC_SEQ_CST)

#define ATOMICQ_HEAD(name, type)					\
struct name {								\
	struct type *aqh_first;						\
}

#define ATOMICQ_ENTRY(type)						\
struct {								\
	struct type *aqe_next;						\
}

#define ATOMICQ_INIT(head) (head)->aqh_first = 0

#define ATOMICQ_PUT(head, elm, field) do {				\
	(elm)->field.aqe_next = (head)->aqh_first;			\
} while (!cmpxchg(&(head)->aqh_first, &(elm)->field.aqe_next, &(elm)))

#define ATOMICQ_GET(head, elm, field) do {				\
	(elm) = (head)->aqh_first;					\
	if (!(elm))							\
		break;							\
} while (!cmpxchg(&(head)->aqh_first, &(elm), &(elm)->field.aqe_next));

#endif /* _SYS_ATOMIC_H */
