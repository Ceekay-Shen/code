#include <hashtable.h>


HASH_TABLE_S *HashTable_Creat(u32(*hash_value)(HASH_TABLE_S *h, const void *key),
                              int(*keycmp)(struct HASH_TABLE_S *h, const void *key1, const void *key2),
                              u32 size)
{
    HASH_TABLE_S *pstHashTable = NULL;
    u32 i;

    if (size <= 0 || NULL == hash_value || NULL == keycmp)
    {
        return pstHashTable;
    }


    pstHashTable = zalloc(sizeof(HASH_TABLE_S));
    if (NULL == pstHashTable)
    {
        return pstHashTable;
    }

    pstHashTable->size = size;
    pstHashTable->count = 0;
    pstHashTable->hash_value = hash_value;
    pstHashTable->keycmp = keycmp;

    pstHashTable->htable = malloc(size * sizeof(*pstHashTable->htable));
    if(NULL == pstHashTable->htable)
    {
        free(pstHashTable);
        return NULL;
    }

    for(i = 0; i < size; i ++)
    {
        pstHashTable->htable[i] = NULL;
    }
    
    return pstHashTable;
}


int Hash_Table_Insert(HASH_TABLE_S *h, void *key, void *datum)
{
    u32 hvalue;
    HASH_NODE_S *prev, *cur, *newnode;

    if(NULL == h || MAXINUM_CAPACITY == h->count)
        return -1;

    hvalue = h->hash_value(h, key);

    prev = NULL;
    cur = h->htable[hvalue];

    while(cur && h->keycmp(h, key, cur->key) > 0)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur && (h->keycmp(h, key, cur->key)==0))
    {
        return -1;
    }

    newnode = malloc(sizeof(HASH_NODE_S));
    memset(newnode, 0, sizeof(HASH_NODE_S));

    if(NULL == newnode)
    {
        return -1;
    }

    newnode->key = key;
    newnode->datum = datum;

    if(prev)
    {
        newnode->next = prev->next;
        prev->next = newnode;
    }
    else
    {
        newnode->next = h->htable[hvalue];
        h->htable[hvalue] = newnode;
    }

    h->count++;
    return 0;
}


void *Hash_Table_Search(HASH_TABLE_S *h, const void *key)
{
    u32 hvalue;
    HASH_NODE_S *cur;

    if(NULL == h)
    {
        return NULL;
    }

    hvalue = h->hash_value(h,key);
    cur = h->hash_value[hvalue];

    while(NULL !=cur || (h->keycmp(h,key,cur->key) > 0))
    {
        cur = cur->next;
    }

    if(NULL == cur || (h->keycmp(h, key, cur->key) != 0))
    {
        return NULL;
    }

    return cur->datum;
        
}

void Hash_Table_Destory(HASH_TABLE_S *h)
{
    u32 i;
    HASH_NODE_S *cur, *tmp;

    if (NULL == h)
    {
        return ;
    }

    for (i == 0; i < h->size; i++)
    {
        cur = h->htable[i];
        while(cur)
        {
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        h->htable[i] = NULL;
    }

    free(h->htable);
    h->htable = NULL;

    free(h);
}




