#ifndef _LIST_H
#define _LIST_H

struct list_head{
    struct list_head *next;
    struct list_head *prev;

}LIST_HEAD_ST;


#define LIST_HEAD_INIT(name) {&(name),&(name)}

#define LIST_HEAD(name) \
    LIST_HEAD_ST name = LIST_HEAD_INIT(name)


#define INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); \
    (ptr)->prev = (ptr); \
}while(0)


static __inline__ void __list_add(LIST_HEAD_ST *new, 
                                  LIST_HEAD_ST *prev,
                                  LIST_HEAD_ST *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}


void list_add(LIST_HEAD_ST *new, LIST_HEAD_ST *head)
{
    __list_add(new, head,head->next);
}

void list_add_tail(LIST_HEAD_ST *new, LIST_HEAD_ST *head)
{
    __list_add(new,head->prev,head);
}

static __inline__ void __list_del(LIST_HEAD_ST *prev, LIST_HEAD_ST *next)
{
    next->prev = prev;
    prev->next = next; 
}

void list_del(LIST_HEAD_ST *entry)
{
    __list_del(entry->prev, entry->next);
}


#endif