#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

static size_t hash_function(const char* key);

int main(void)
{

    init_hashmap_malloc(1, hash_function);
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
