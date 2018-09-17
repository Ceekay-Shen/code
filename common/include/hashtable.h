#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#define DEFAULT_INIITAL_CAPACITY  (1 << 4) 

#define MAXINUM_CAPACITY (1 << 30)

#define DEFAULT_LOAD_FACTOR  0.75f

#define TREEIFY_THRESHOLD 8

#define UNTREEIFY_THRESHOLD 6

#define MIN_TREEILY_CAPACITY 64

typedef struct Hash_Node{
    void *key;
    void *datum;
    struct Hash_Table *next;
}HASH_NODE_S;


typedef struct Hash_Table{
    HASH_NODE_S **htable;
    u32 size;
    u32 count;
    u32 (*hash_value)(struct Hash_Table *h, const void key);
    int (*keycmp)(struct Hash_Table *h, const void *key1, const void *key2);
}HASH_TABLE_S;

typedef struct hashtable_info{
    u32 slots_used;
    u32 max_chain_len;
}










#endif