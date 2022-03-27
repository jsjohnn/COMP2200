#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;

    hashmap_t* hashmap_p = NULL;
    hashmap_p = malloc(sizeof(hashmap_t));

    hashmap_p->length = length;
    hashmap_p->hash_func = p_hash_func;
    
    hashmap_p->plist = malloc(length * sizeof(node_t*));

    for (i = 0; i < length; ++i) {
        hashmap_p->plist[i] = NULL;
    }

    return hashmap_p;


}

/*
typedef struct node {
    char* key;
    int value;
    struct node* next;
} node_t;
*/

void destroy(hashmap_t* hashmap)
{2
    size_t i;
    node_t* tmp;

    size_t len = hashmap->length;

    while ((*(hashmap->plist))->next != NULL) {
        tmp = (*(hashmap->plist))->next;
        free(*(hashmap->plist));
        *(hashmap->plist) = tmp;
    }
    free(*(hashmap->plist));

    free(hashmap);

    
}
