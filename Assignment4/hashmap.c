#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;

    hashmap_t tmp_hashmap;

    tmp_hashmap.hash_func = p_hash_func;
    tmp_hashmap.length = length;

    tmp_hashmap.plist = NULL;
    tmp_hashmap.plist = malloc(sizeof(node_t*) * length);

    for (i = 0; i < length - 1; ++i) {
        hashmap.plist[i] = NULL;
    }


    return &tmp_hashmap;

}

void destroy(hashmap_t* hashmap)
{
    
}
