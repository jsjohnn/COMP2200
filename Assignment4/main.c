#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

static size_t hash_function(const char* key);

int main(void)
{
    hashmap_t* hashmap = NULL;

    hashmap  = init_hashmap_malloc(10, hash_function);

    /* destroy(hashmap); */
    
    return 0;
}

static size_t hash_function(const char* key)
{
    size_t code = 0;
    const char* c = key;

    while (*c != '\0') {
        code += *c++;
    }

    return code;
}
