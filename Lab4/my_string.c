#include <stdio.h>
#include <assert.h>
#include "my_string.h"

/* TODO: 반복문을 index접근이 아닌 포인터 접근으로 가능? */
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

/* TODO: 배열 할당 최소한으로 줄이기 */
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

        if(first_word_same) {
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
                reverse(str- str_move);
                break;
            }

            *--str = 0x00;
            reverse(str- (str_move - 1));
            *str++ = 0x20;

            str_move = 0;

            continue;
        }
    }

}

char* tokenize(char* str_or_null, const char* delims)
{

    static char* start_address;
    static size_t is_continous = 0;

    const char* orign_delims = delims;

    size_t count = 0;
    size_t delims_count = 0;
    size_t is_founded = 0;
    size_t first_char_delims = 0;

    if (str_or_null == NULL && is_continous == 0) {
        return NULL;
    }

    if (str_or_null != NULL && is_continous == 0) {
        start_address = str_or_null;
    }

    while (*delims++ != 0x00) {
        delims_count++;
    }

    if (str_or_null != NULL && str_or_null != start_address) {
        start_address = str_or_null;
    }

    delims = delims - 1 - delims_count;
    assert(*delims == 0x20);

    printf("start_address: %c\n", *(start_address));

    while (*delims != 0x00) {
        if (*start_address == *delims) {
            first_char_delims = 1;
            delims = orign_delims;
            ++start_address;
            break;
        }
        ++delims;
    }

    if (first_char_delims) {
        
        while (*start_address != 0x00) {
            while (*delims != 0x00) {
                if (*start_address != *delims) {
                    first_char_delims = 2;
                    break;
                }

                if (*start_address == 0x20) {
                    *start_address = 0x00;
                }

                ++delims;
            }

            ++start_address;

            if (first_char_delims == 2) {
                break;
            }        

        }

        /* printf("start_address: %c\n", *(start_address)); */
        /* printf("count: %d\n", count); */

        while (*start_address != 0x00) {
            delims = orign_delims;
            ++count;
            while (*delims != 0x00) {
                if (*start_address != *delims) {
                    ++is_continous;

                    return start_address - count;
                }

                if (*start_address == 0x20) {
                    *start_address = 0x00;
                    break;
                }

                ++delims;
            }
            ++start_address;
            
        }
        /* return NULL; */
    }

    while (*start_address != 0x00) {
        ++count;

        while (*delims != 0x00) {
            if (*start_address == *delims) {
                is_founded = 1;

                if (*start_address == 0x20) {
                    *start_address = 0x00;
                }

                break;
            }
            ++delims;

        }
        ++start_address;
        delims = orign_delims;

        if (is_founded == 1) {
            break;
        }
    }
/*
    printf("count: %lu", count);
    printf("is_founded: %lu\n", is_founded);
*/

    if (is_founded == 0) {
        is_continous = 0;
        return start_address - count;
    }

    is_founded = 0;

/* debug start */

    assert(*delims == 0x20);

/* debug end */


    /* printf("start_address: %c,  ", *start_address);
     printf("count: %lu\n", count); */


    while (*start_address != 0x00) {
        ++count;
        while (*delims != 0x00) {
            
            if (*start_address == *delims && *start_address == 0x20) {
                *start_address = 0x00;
                ++delims;

                continue;
            }

            if (*start_address != *delims) {
                is_founded = 1;

                break;
            }

            ++delims;
        }

        if (is_founded == 1) {
            break;
        }

        ++start_address;
        delims = orign_delims;

    }

    /* start_address++; */
    is_continous++;

    printf("start_address: %c\n", *(start_address));
    printf("count: %lu\n", count);
    printf("=======\n");

    return start_address + 1 - count;

}
