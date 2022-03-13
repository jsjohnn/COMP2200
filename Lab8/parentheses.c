#include <stdio.h>
#include <string.h>

#include "parentheses.h"

#define LENGTH (4096)

size_t get_matching_parentheses(parenthesis_t* out_parentheses, size_t max_size, const char* str)
{
    char my_str[LENGTH];
    char* my_str_p = my_str;

    size_t struct_num = 0;

    size_t cur_opening_index = 0;
    size_t cur_closing_index = 0;
    size_t cur_index = -1;

    size_t fnd_closing_cnt;
    size_t skip_num = 0;

    const size_t str_length = strlen(str);

    strncpy(my_str, str, str_length + 1);

    while (*my_str_p != '\0') {
        if (struct_num == max_size) {
            break;
        }
     
        ++cur_index;
        
        if (*my_str_p == '{') {

            cur_opening_index = cur_index;
            cur_closing_index = cur_index + 1;
            ++my_str_p;

            fnd_closing_cnt = 0;
            skip_num = 0;

            while (*my_str_p != '\0') {
                ++fnd_closing_cnt;

                if (*my_str_p == '}') {
                    if (skip_num == 0) {
                        out_parentheses->opening_index = cur_opening_index;
                        out_parentheses->closing_index = cur_closing_index;

                        out_parentheses++;
                        struct_num++;

                        my_str_p -= fnd_closing_cnt;
                        break;
                       

                    } else {
                        --skip_num;
                    }

                } else if (*my_str_p == '{') {
                    ++skip_num;
                }

                ++cur_closing_index;
                ++my_str_p;

                if (*my_str_p == '\0') {
                     my_str_p = my_str_p - 1 - fnd_closing_cnt;
                     break;
                }
            }
            
        } else if (*my_str_p == '<') {
           cur_opening_index = cur_index;
            cur_closing_index = cur_index + 1;
            ++my_str_p;

            fnd_closing_cnt = 0;
            skip_num = 0;

            while (*my_str_p != '\0') {
                ++fnd_closing_cnt;

                if (*my_str_p == '>') {
                    if (skip_num == 0) {
                        out_parentheses->opening_index = cur_opening_index;
                        out_parentheses->closing_index = cur_closing_index;

                        out_parentheses++;
                        struct_num++;

                        my_str_p -= fnd_closing_cnt;
                        break;
                       

                    } else {
                        --skip_num;
                    }

                } else if (*my_str_p == '<') {
                    ++skip_num;
                }

                ++cur_closing_index;
                ++my_str_p;

                if (*my_str_p == '\0') {
                     my_str_p = my_str_p  - 1 - fnd_closing_cnt;
                     break;
                }
            }
        } else if (*my_str_p == '(') {
           cur_opening_index = cur_index;
            cur_closing_index = cur_index + 1;
            ++my_str_p;

            fnd_closing_cnt = 0;
            skip_num = 0;

            while (*my_str_p != '\0') {
                ++fnd_closing_cnt;

                if (*my_str_p == ')') {
                    if (skip_num == 0) {
                        out_parentheses->opening_index = cur_opening_index;
                        out_parentheses->closing_index = cur_closing_index;

                        out_parentheses++;
                        struct_num++;

                        my_str_p -= fnd_closing_cnt;
                        break;
                       

                    } else {
                        --skip_num;
                    }

                } else if (*my_str_p == '(') {
                    ++skip_num;
                }

                ++cur_closing_index;
                ++my_str_p;

                if (*my_str_p == '\0') {
                     my_str_p = my_str_p  - 1 - fnd_closing_cnt;
                     break;
                }
            }
        } else if (*my_str_p == '[') {
           cur_opening_index = cur_index;
            cur_closing_index = cur_index + 1;
            ++my_str_p;

            fnd_closing_cnt = 0;
            skip_num = 0;

            while (*my_str_p != '\0') {
                ++fnd_closing_cnt;

                if (*my_str_p == ']') {
                    if (skip_num == 0) {
                        out_parentheses->opening_index = cur_opening_index;
                        out_parentheses->closing_index = cur_closing_index;

                        out_parentheses++;
                        struct_num++;

                        my_str_p -= fnd_closing_cnt;
                        break;
                       

                    } else {
                        --skip_num;
                    }

                } else if (*my_str_p == '[') {
                    ++skip_num;
                }

                ++cur_closing_index;
                ++my_str_p;

                if (*my_str_p == '\0') {
                     my_str_p = my_str_p  - 1 - fnd_closing_cnt;
                     break;
                }
            }
        }
        
        ++my_str_p;
    }
    
    

    return struct_num;
}
