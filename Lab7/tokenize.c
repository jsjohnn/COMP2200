#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tokenize.h"

#define INCREMENT (2)


/* static 키워드 붙이기 */
const char* get_next_pointer_or_null(const char* str, const char* delim);

char** tokenize_malloc(const char* str, const char* delim)
{
    const char* str_start = str;
    const char* str_cur = str;

    const char* my_delim = delim;

    size_t max_tokens = 0;
    size_t num_tokens = 0;

    size_t len;
    size_t after_delim = 0;

    char** tokens;
    char** tmp;
    char* tmp_2;

    tokens = NULL;

    if (strlen(str) == 0 && *str == '\0') {
        tmp = malloc(sizeof(char*));
        tokens = tmp;
        *tokens = NULL;
        return tokens;
    }


    if (strlen(delim) == 0 && *delim == '\0') {
        goto TOKENIZE_START;
    }
/*
    if (strlen(str) == 0 || strlen(delim) == 0) {
        return NULL;
    }
*/

    while (*str_cur != '\0') {
        while (*my_delim != '\0') {
            if (*str_cur == *my_delim) {
                my_delim = delim;
                break;
            } 
            ++my_delim;

            if (*my_delim == '\0') {
                str_start = str_cur;
                ++str_cur;
                my_delim = delim;
                goto TOKENIZE_START;
            }
        }

        my_delim = delim;
        ++str_cur;
    }

    return NULL;


TOKENIZE_START:

    /* tmp 해제는?? */
    tmp = malloc(INCREMENT * sizeof(char*));
    tokens = tmp;
    max_tokens += INCREMENT;
    

    while (*str_cur != '\0') {
        if (max_tokens == num_tokens) {
            tmp = realloc(tokens, (max_tokens + INCREMENT) * sizeof(char*));
            tokens = tmp;
            max_tokens += INCREMENT;
        }

        while (*my_delim != '\0') {
            if (*str_cur == *my_delim) {
                len = str_cur - str_start + 1;
                tmp_2 = malloc(len);
                tokens[num_tokens] = tmp_2;               

                memcpy(tokens[num_tokens], str_start, len - 1);
                tokens[num_tokens++][len - 1] = '\0';

                str_cur = get_next_pointer_or_null(++str_cur, delim);

                if (*str_cur == '\0') {
                    goto TOKENIZE_EXIT_2;
                }

                str_start = str_cur;

                break;

            }

            ++my_delim;
        }

        my_delim = delim;
        ++str_cur;
        
    }

TOKENIZE_EXIT:

    if (*str_cur == '\0') {
        if (max_tokens == num_tokens) {
            tmp = realloc(tokens, (max_tokens + 1) * sizeof(char*));
            tokens = tmp;
            ++max_tokens;
        }

        len = str_cur - str_start + 1;
        tmp_2 = malloc(len);
        tokens[num_tokens] = tmp_2;               

        memcpy(tokens[num_tokens], str_start, len - 1);
        tokens[num_tokens++][len - 1] = '\0';
        tokens[num_tokens] = NULL;
        return tokens;

    }

    
    

TOKENIZE_EXIT_2:

    if (max_tokens == num_tokens) {
        tmp = realloc(tokens, (max_tokens + 1) * sizeof(char*));
        tokens = tmp;
        tokens[++num_tokens] = NULL;
    } else {
        tokens[num_tokens] = NULL;
    }

    return tokens;

}

/* TODO: or null 을 삭제하고 널 문자를 만나면 널 문자를 반환하도록 수정 */

const char* get_next_pointer_or_null(const char* str, const char* delim)
{
    const char* s_delim = delim;

    while (*str != '\0') {
        while (*s_delim != '\0') {
            if (*str == *s_delim) {
                break;
            }

            ++s_delim;
 
            if (*s_delim == '\0') {
                return str;
            }
        }

        ++str;
        s_delim = delim;
    }

    return str;
}

