#include <assert.h>
#include <stdio.h>

#define TRUE (1)

size_t get_str_length(const char* const str);

void reverse(char* str)
{
    size_t str_length = get_str_length(str);

    char* p_front_char = str;
    char* p_rear_char = str + str_length - 1;

    assert(str != NULL);

    while (p_front_char < p_rear_char) {
        *p_front_char = *p_front_char ^ *p_rear_char;
        *p_rear_char = *p_front_char ^ *p_rear_char;
        *p_front_char = *p_front_char ^ *p_rear_char;

        ++p_front_char;
        --p_rear_char;
    }
}

int index_of(const char* str, const char* word)
{
    const char* p_word;
    const char* p_word_start_in_str;

    assert(str != NULL && word != NULL);

    if (*word == '\0') {
        return 0;
    }

    for (p_word_start_in_str = str; *p_word_start_in_str != '\0'; ++p_word_start_in_str) {
        const char* p_current_position = p_word_start_in_str;

        p_word = word;
        while (*p_current_position++ == *p_word++) {

            if (*p_word == '\0') {
                return p_word_start_in_str - str;
            }   
        }
    }

    return -1;
}

void reverse_by_words(char* str)
{
    char* p_str = str;

    size_t current_word_length = 0;
    
    assert(str != NULL);

    while (*p_str != '\0') {
        char* p_word_start = p_str;
        char* p_word_end;

        current_word_length ^= current_word_length;
        while (*p_str != '\0' && *p_str++ != ' ') {
            ++current_word_length;
        }

        p_word_end = p_word_start + current_word_length - 1;

        while (p_word_start < p_word_end) {
            *p_word_start = *p_word_start ^ *p_word_end;
            *p_word_end = *p_word_start ^ *p_word_end;
            *p_word_start = *p_word_start ^ *p_word_end;

            ++p_word_start;
            --p_word_end;
        }
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* s_p_str_indicator = NULL;

    const char* p_delims;

    char* p_token_start;
    char* p_str;

    assert(delims != NULL);

    if (str_or_null == NULL) {
        if (s_p_str_indicator == NULL || *s_p_str_indicator == '\0') {
            return NULL;
        }        

        p_str = s_p_str_indicator;

    } else {
        if (*str_or_null == '\0') {
            return NULL;
        }

        p_str = str_or_null;
    }

    while (TRUE) {

        p_delims = delims;
        while (*p_str != *p_delims++) {

            if (*p_delims == '\0') {
                ++p_str;
                goto tokenize_start;
            }
        }

        if (*++p_str == '\0') {
            return NULL;
        }
    }

tokenize_start:

    
    p_token_start = p_str - 1;
    while (*p_str != '\0') {
    
        for (p_delims = delims; *p_delims != '\0'; ++p_delims) {

            if (*p_str == *p_delims) {
                *p_str++ = '\0';

                goto exit_to_end;
            }
        }

        ++p_str;
    }

exit_to_end:

    s_p_str_indicator = p_str;

    return p_token_start;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* p_token = tokenize(str_or_null, delims);

    if (p_token == NULL) {
        return NULL;
    }

    reverse(p_token);

    return p_token;
}

size_t get_str_length(const char* const str)
{
    const char* p_str = str;

    assert(str != NULL);

    while (*p_str++ != '\0') {
        /* It wasn`t NUL */
    }

    return p_str - str - 1;
}
