#include <stdio.h>
#include <assert.h>
#include "my_string.h"

void reverse(char* str)
{
    char* dec_str = str;

    while (*dec_str++ != '\0') {
    }

    dec_str = dec_str - 2;

    while (str < dec_str) {
        *str = *str ^ *dec_str;
        *dec_str = *str ^ *dec_str;
        *str = *str ^ *dec_str;

        ++str;
        --dec_str;
    }

}

int index_of(const char* str, const char* word)
{
    const char* copied_word = word;
    const char* copied_str = str;
    const char* first_address;

    size_t first_word_same;
    size_t word_same;

    size_t word_count;
    size_t word_left_count;


    if (str == NULL || word == NULL) {
        return -1;
    }

    if (*word == '\0') {
        return 0;
    }
    
    while (*copied_word++ != '\0') {
    }

    word_count = copied_word - 1 - word;
    word_left_count = word_count;

    copied_word = word;

    while (*copied_str != '\0') {
        first_word_same = *copied_str++ == *copied_word;

        if (first_word_same) {
            first_address = copied_str - 1;
            --word_left_count;

            if (word_left_count == 0) {
                return first_address - str;
            }

            while (*copied_str != '\0') {
                word_same = *copied_str++ == *++copied_word;
                if (!word_same) {
                    word_left_count = word_count;
                    copied_word = word;
                    copied_str = first_address + 1;
                    break;
                }

                word_left_count--;

                if (word_left_count == 0) {
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

    while (*str != 0x00) {
        is_space = (*str++ == ' ') || (*str == '\0');
        ++str_move;

        if (is_space) {
            if (*str =='\0') {
                reverse(str - str_move);
                break;
            }

            *--str = '\0';
            reverse(str - (str_move - 1));
            *str++ = ' ';

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
    const char* end_chk_str;
    
    char* tmp_str;
    size_t count = 0;
    size_t end_count = 0;
    size_t not_end_flag = 0;  
    
    if (s_is_continue == 0 && str_or_null == NULL) {
        return NULL;
    }
    
    if (s_is_continue == 0 && str_or_null != NULL) {
        s_str = str_or_null;
    }

    if (str_or_null != NULL && *str_or_null != *s_str) {
        s_is_continue = 0;
        s_str = str_or_null;
    }

    if (s_is_continue > 0) {
        str_or_null = s_str;
    }

    if (s_str == NULL) {
        return NULL;
    }

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
            tmp_str = s_str;
            s_str = NULL;
            return tmp_str;
        }

    }

    end_chk_str = str_or_null + 1;

    if (*end_chk_str == '\0') {
        s_is_continue = 0;
        tmp_str = s_str;
        s_str = NULL;
        return tmp_str;
    }

    while (*end_chk_str != '\0') {
        delims = orign_delims;
        while (*delims != '\0') {
            if (*end_chk_str != *delims) {
                ++end_count;
            }

            ++delims;
        }

        if (end_count == (size_t)(delims - orign_delims)) {
            not_end_flag = 1;
            break;
        }
        ++end_chk_str;
        end_count = 0;
    }
                
    if (not_end_flag != 1) {
        s_is_continue = 0;
        tmp_str = s_str;
        s_str = NULL;
        return tmp_str;
    }

    count = str_or_null - s_str;

    s_str = str_or_null + 1;
    
    ++s_is_continue;
    
    return s_str - 1 - count;
    
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* my_token = tokenize(str_or_null, delims);

    if (my_token == NULL) {
        return NULL;
    }
    reverse(my_token);

    return my_token;
    
}



