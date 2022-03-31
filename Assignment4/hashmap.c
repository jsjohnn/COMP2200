#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;

    hashmap_t* hashmap_p = malloc(sizeof(hashmap_t));

    hashmap_p->length = length;
    hashmap_p->hash_func = p_hash_func;
    
    hashmap_p->plist = malloc(length * sizeof(node_t*));

    for (i = 0; i < length; ++i) {
        hashmap_p->plist[i] = NULL;
    }

    return hashmap_p;

}

void destroy(hashmap_t* hashmap)
{
    
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{

    size_t key_length = strlen(key);
    char* tmp_key;
    node_t* tmp_node;

    size_t i;
    size_t hash_length = hashmap->length;


#if 0
    if (key == "" || key == NULL) {
        return FALSE;
    }
#endif


    /* 요소가 하나도 없을 때 추가하는 로직, 나중에 하나로 합칠 수 있으면 합치기 */
    if (*(hashmap->plist) == NULL) {
        tmp_node = malloc(sizeof(node_t));
        *(hashmap->plist) = tmp_node;

        tmp_key = malloc(key_length + 1);
        (*(hashmap->plist))->key = tmp_key;

        strncpy((*(hashmap->plist))->key, key, key_length);
        (*(hashmap->plist))->key[key_length] = '\0';
        (*(hashmap->plist))->value = value;
        (*(hashmap->plist))->next = NULL;

        return TRUE;
    }

    for (i = 0; i < hash_length; ++i) {

        if (hashmap->plist[i] == NULL) {
            /* add add logic */

            tmp_node = malloc(sizeof(node_t));
            hashmap->plist[i] = tmp_node;


            tmp_key = malloc(key_length + 1);
            hashmap->plist[i]->key = tmp_key;

            strncpy(hashmap->plist[i]->key, key, key_length);

            hashmap->plist[i]->key[key_length] = '\0';
            hashmap->plist[i]->next = NULL;
            hashmap->plist[i]->value = value;

            hashmap->plist[i - 1]->next = hashmap->plist[i];

            return TRUE;


        } else if (strcmp(hashmap->plist[i]->key, key) == 0) {
            return FALSE;
        } else {
            continue;
        }
        
    }

    return FALSE;
}






