#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

#define DEFAULT_ARRAY_LENGTH (20)


static size_t hash_function(const char* key);
static void print_hashmap(hashmap_t* hashmap);

int main(void)
{
    
    size_t i = 0;
    hashmap_t* hashmap = NULL;

    hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);

    for (i = 0; i < 100; i++) {
        char key[100];
        int value = (int)i;
        int c;
        int dummy = 512;

        sprintf(key, "key%u", i);

        assert(add_key(hashmap, key, value) == TRUE);

        c = get_value(hashmap, key);
        assert(c == value);

        assert(add_key(hashmap, key, dummy) == FALSE);

        c = get_value(hashmap, key);
        assert(c == value);
    }

    for (i = 0; i < 100; i++) {
        char key[100];
        int value = (int)(i * i * i);
        int c;

        sprintf(key, "key%u", i);

        assert(update_value(hashmap, key, value) == TRUE);
        c = get_value(hashmap, key);

        assert(c == value);
    }

    print_hashmap(hashmap);

    for (i = 0; i < 100; i++) {
        char key[100];
        int c;

        sprintf(key, "key%u", i);

printf("%s\n", key);


if (strcmp(key, "key10") == 0) {
    print_hashmap(hashmap);

}

        assert(remove_key(hashmap, key) == TRUE);
        c = get_value(hashmap, key);

        assert(c == -1);


        assert(remove_key(hashmap, key) == FALSE);


puts("===========================");
    }


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



static void print_hashmap(hashmap_t* hashmap)
{
    size_t i;

    for (i = 0; i < hashmap->length; ++i) {
        node_t* p_node = hashmap->plist[i];
        size_t j = 0;
        printf("index:[%d]\n", i);

        while (p_node != NULL) {
            printf("node_count:[%d] key: %s , value: %d hash_val: %d\n", j++, p_node->key, p_node->value, hash_function(p_node->key) % DEFAULT_ARRAY_LENGTH);

            p_node = p_node->next;
        }
    }
}


