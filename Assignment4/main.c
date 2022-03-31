#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

#define DEFAULT_ARRAY_LENGTH (20)


static size_t hash_function(const char* key);
/* static void print_hashmap(hashmap_t* hashmap); */

int main(void)
{
    size_t i;

    hashmap_t* hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);

    printf("%lu\n", hash_function("str") % 3 );
    printf("%lu\n", hash_function("is the best") % 3);
    printf("%lu\n", hash_function("pocu") % 3);
    printf("%lu\n", hash_function("is") % 3);
    printf("%lu\n", hash_function("the") % 3);
    printf("%lu\n", hash_function("best") % 3);
    printf("%lu\n", hash_function("programming") % 3);
    printf("%lu\n", hash_function("school") % 3);

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


/*
static void print_hashmap(hashmap_t* hashmap)
{
    size_t i;

    for (i = 0; i < hashmap->length; ++i) {
        node_t* p_node = hashmap->plist[i];
        size_t j = 0;
        printf("index:[%d]\n", i);

        while (p_node != NULL) {
            printf("node_count:[%d] key: %s , value: %d\n", j++, p_node->key, p_node->value);

            p_node = p_node->next;
        }
    }
}
*/

