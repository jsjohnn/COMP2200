#include <stdio.h>
#include <assert.h>
#include "my_string.h"

void reverse(char* str)
{
    size_t i = 0;
    size_t count = 0;
    size_t half;

    while (*str++ != 0x00) {
        ++count;
    }

    str = str - 1 - count;

    if (count < 2) {
        return;
    }

    half = count / 2;

    for (i = 0; i < half; ++i) {
        str[i] ^= str[count - 1 - i];
        str[count - 1 - i] ^= str[i];
        str[i] ^= str[count - 1 - i];
    }

}

int index_of(const char* str, const char* word)
{
    const char* copy_word = word;
    const char* copy_str = str;
    const char* first_address;

    size_t first_word_same;
    size_t word_same;
    size_t word_count;
    size_t left_count;


    if (str == NULL || word == NULL) {
        return -1;
    }

    if (*word == 0x00) {
        return 0;
    }

    while (*copy_word++ != 0x00) {
    }

    word_count = copy_word - 1 - word;
    left_count = word_count;

    copy_word = word;

    while (*copy_str != 0x00) {
        first_word_same = *copy_str++ == *copy_word;

        if (first_word_same) {
            first_address = copy_str - 1;
            --left_count;

            if (left_count == 0) {
                return first_address - str;
            }

            while (*copy_str != 0x00) {
                word_same = *copy_str++ == *++copy_word;
                if (!word_same) {
                    left_count = word_count;
                    copy_word = word;
                    copy_str = first_address + 1;
                    break;
                }

                left_count--;

                if (left_count == 0) {
                    return first_address - str;
                }
            }
        }
    }

    return -1;
}

void reverse_by_words(char* str)
{
    size_t is_space = 0;
    size_t str_move = 0;
    size_t str_length = 0;

    const char* copy_str = str;

    while (*copy_str++ != 0x00) {
        ++str_length;
    }

    while (*str != 0x00) {
        is_space = (*str++ == 0x20) || (*str == 0x00);
        ++str_move;

        if (is_space) {
            if (*str == 0x00) {
                reverse (str- str_move);
                break;
            }

            *--str = 0x00;
            reverse (str- (str_move - 1));
            *str++ = 0x20;

            str_move = 0;

            continue;
        }
    }

}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* s_str;
    static int s_is_continue = 0;
    
    const char* orign_delims = delims;
    
    size_t count = 0;
    size_t added_null = 0;

    if (s_is_continue == 0 && str_or_null == NULL) {
        return NULL;
    }

    if (s_is_continue == 0 && str_or_null != NULL) {
        s_str = str_or_null;
    }

    if (s_is_continue >= 0) {
        str_or_null = s_str;
    } else {
        return NULL;
    }

    

    /* if (s_is_continue != 0 && * (s_str - 1) == '\0') {
        return NULL;
    }  */
/*
    printf("=-=-=-==-=-=-==-=-=-==-=-=-=\n");
    printf("str_or_null: %c\n", *str_or_null);
*/

    while (*str_or_null != '\0') {

        while (*delims != '\0') {
            if (*str_or_null == *delims) {
                break;
            } else {
                ++delims;
                continue;
            }

        }
        
        if (*str_or_null != *delims) {
            s_str = str_or_null;
            delims = orign_delims;
            break;
        }

        delims = orign_delims;
        ++str_or_null;

        

    }

    ++str_or_null;

    while (*str_or_null != '\0') {
        while (*delims != '\0') {
            if (*str_or_null == *delims) {
                break;
            } else {
                ++delims;
                continue;
            }
        }

        if (*str_or_null == *delims) {
            *str_or_null = '\0';
            break;
        }
        ++str_or_null;
        delims = orign_delims;

        if (*str_or_null == '\0') {
            s_is_continue = 0;
            s_str = 0;
            return s_str;
        }
    }

    /* printf("this_str_or_null: %c\n", *(str_or_null - 1)); */

    count = str_or_null - s_str;

    s_str = str_or_null + 1;
    
    ++s_is_continue;

    if (*(s_str) == '\0') {
        s_is_continue = -1;
    }
/*    
    printf("return string: %s\n", s_str - 1 - count);
    printf("count: %d\n", count);
    printf("str_or_null: %s\n", str_or_null);
    printf("s_str :%s\n", s_str);
*/
    return s_str - 1 - count;
    
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* my_token = tokenize(str_or_null, delims);
    reverse(my_token);

    return my_token;
    
}
