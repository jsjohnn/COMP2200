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

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    size_t key_len = strlen(key);
    size_t hash_value = hashmap->hash_func(key) % hashmap->length;
    node_t* add_node;

    /* 해당 해시 값 인덱스에 값이 존재하지 않는 경우 */
    if (hashmap->plist[hash_value] == NULL) {

        hashmap->plist[hash_value] = malloc(sizeof(node_t));
        hashmap->plist[hash_value]->value = value;
        hashmap->plist[hash_value]->next = NULL;
        hashmap->plist[hash_value]->key = malloc(key_len + 1);
        strncpy(hashmap->plist[hash_value]->key, key, key_len);
        hashmap->plist[hash_value]->key[key_len] = '\0';

        return TRUE;

    } else {
        node_t* temp_node_t = hashmap->plist[hash_value];

        if (strcmp(temp_node_t->key, key) == 0) {
            return FALSE;
        }

        while (temp_node_t->next != NULL) {
            if (strcmp(temp_node_t->key, key) == 0) {
                return FALSE;
            }

            temp_node_t = temp_node_t->next;

            if (temp_node_t->next == NULL) {
                if (strcmp(temp_node_t->key, key) == 0) {
                    return FALSE;
                }
            }

        }

        add_node = malloc(sizeof(node_t));

        add_node->key = malloc(key_len + 1);
        strncpy(add_node->key, key, key_len);
        add_node->key[key_len] = '\0';

        add_node->value = value;
        add_node->next = NULL;

        temp_node_t->next = add_node;

        return TRUE;

    }

    return FALSE;

}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash_value = hashmap->hash_func(key) % hashmap->length;

    if (hashmap->plist[hash_value] == NULL) {
        return -1;
    } else if (hashmap->plist[hash_value]->next == NULL) {
        if (strcmp(hashmap->plist[hash_value]->key, key) != 0) {
            return -1;
        } else {
            return hashmap->plist[hash_value]->value;
        }
    } else {
        node_t* temp_node_t = hashmap->plist[hash_value];
        
        while (temp_node_t->next != NULL) {
            if (strcmp(temp_node_t->key, key) == 0) {
                return temp_node_t->value;
            }
            
            temp_node_t = temp_node_t->next;
        }

        if (strcmp(temp_node_t->key, key) == 0) {
            return temp_node_t->value;
        }
        
    }
    
    return -1;

}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash_value = hashmap->hash_func(key) % hashmap->length;

    if (hashmap->plist[hash_value] == NULL) {
        return FALSE;
    } else if (hashmap->plist[hash_value]->next == NULL) {
        if (strcmp(hashmap->plist[hash_value]->key, key) == 0) {
            hashmap->plist[hash_value]->value = value;
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        node_t* temp_node_t = hashmap->plist[hash_value];
        
        while (temp_node_t->next != NULL) {
            if (strcmp(temp_node_t->key, key) == 0) {
                temp_node_t->value = value;
                return TRUE;
            }
            temp_node_t = temp_node_t->next;
        }

        if (strcmp(temp_node_t->key, key) == 0) {
            temp_node_t->value = value;
            return TRUE;
        } else {
            return FALSE;
        }

    }
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t hash_value = hashmap->hash_func(key) % hashmap->length;

    if (hashmap->plist[hash_value] == NULL) {
        return FALSE;

    } else if (strcmp(hashmap->plist[hash_value]->key, key) == 0) {
        if (hashmap->plist[hash_value]->next == NULL) {

            node_t** tmp_pp = &(hashmap->plist[hash_value]);
            node_t* tmp_p = *tmp_pp;

            free(tmp_p->key);
            tmp_p->key = NULL;

            free(tmp_p);
            *tmp_pp = NULL;

            return TRUE;

        } else {
            node_t** tmp_pp = &(hashmap->plist[hash_value]);
            node_t* tmp_p = hashmap->plist[hash_value];
            *tmp_pp = tmp_p->next;

            free(tmp_p->key);
            tmp_p->key = NULL;

            free(tmp_p);
            tmp_p = NULL;

            return TRUE;
             
        }
    } else {
        node_t** tmp_pp = &(hashmap->plist[hash_value]);
        node_t* tmp_p = hashmap->plist[hash_value];

        while (*tmp_pp != NULL) {
            tmp_p = *tmp_pp;
            if (strcmp(tmp_p->key, key) == 0) {
                (*(--tmp_pp))->next = tmp_p->next;

                free(tmp_p->key);
                tmp_p->key = NULL;

                free(tmp_p);
                tmp_p = NULL;
         
                return TRUE;
            }

            
            tmp_pp = &(tmp_p->next);
            
        }

    }

    return FALSE;

    
}

void destroy(hashmap_t* hashmap)
{
    size_t i;
    size_t length = hashmap->length;

    for (i = 0; i < length; ++i) {
        node_t** tmp_pp = &(hashmap->plist[i]);
        node_t* tmp_p;

        while (*tmp_pp != NULL) {
            tmp_p = *tmp_pp;
            free(tmp_p->key);
            tmp_p->key = NULL;

            tmp_pp = &(tmp_p->next);
            free(tmp_p);

            tmp_p = NULL;
            
        }
        

    }

    free(hashmap->plist);
    free(hashmap);
}


