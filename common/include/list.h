#ifndef _LIST_H
#define _LIST_H

typedef struct list_head{
    struct list_head *next;
    struct list_head *prev;

}LIST_HEAD_ST;


#define LIST_HEAD_INIT(name) {&(name),&(name)}

#define LIST_HEAD(name) \
    LIST_HEAD_ST name = LIST_HEAD_INIT(name)


#define INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
}while(0)


static __inline__ void __list_add(LIST_HEAD_ST *entry,
                                  LIST_HEAD_ST *prev,
                                  LIST_HEAD_ST *next)
{
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;

    return;
}


void list_add(LIST_HEAD_ST *entry, LIST_HEAD_ST *head)
{
    __list_add(entry, head,head->next);

    return;
}

void list_add_tail(LIST_HEAD_ST *entry, LIST_HEAD_ST *head)
{
    __list_add(entry,head->prev,head);

    return;
}

static __inline__ void __list_del(LIST_HEAD_ST *prev, LIST_HEAD_ST *next)
{
    next->prev = prev;
    prev->next = next;
    
    return;
}

void list_del(LIST_HEAD_ST *entry)
{
    __list_del(entry->prev, entry->next);

    return;
}

static __inline__ void list_del_init(LIST_HEAD_ST *entry)
{
    __list_del(entry->prev, entry->prev);
    INIT_LIST_HEAD(entry);

    return;
}


static __inline__ int list_empty(LIST_HEAD_ST *head)
{
    return head->next == head;
}

static __inline__ void list_splice(LIST_HEAD_ST *list, LIST_HEAD_ST *head)
{
    LIST_HEAD_ST *first = list->next;
    LIST_HEAD_ST *last = list->prev;
    LIST_HEAD_ST *at = head->next;

    if (first != list)
    {
        first->prev = head;
        head->next = first;

        last->next = at;
        at->prev = last;
    }

    return;
}


#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))


#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)


#endif