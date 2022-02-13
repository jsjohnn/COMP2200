#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "translate.h"

#define SET_LENGTH (1024)
#define BUFFER_LENGTH (1024)

int translate(int argc, const char** argv)
{ 
    char set1[SET_LENGTH] = "";
    char set2[SET_LENGTH] = "";
    char dummy[SET_LENGTH] = "";

    char buffer[BUFFER_LENGTH] = "";
    char* buffer_p = buffer;

    char* set1_p = set1;
    char* set2_p = set2;
    char* dummy_p = dummy;

    const char* temp = "";

    /*                    '\', 'a','b', 'f', 'n', 'r', 't', 'v' ''' , '"' */
    char escape_char[] = { 92, 97, 98, 102, 110, 114, 116, 118, 39, 34, 0 };

    char* escape_char_p = escape_char;

    size_t is_backslash = 0;
    size_t is_escape_char = 0;

    error_code_t err_code;

    int is_flag = 0;


    if (argc < 3 || argc > 4) {
        err_code = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        return err_code;
    }

    if (argc == 4) {
        if (strlen(argv[1]) == 2 && *argv[1]++ == '-' && *argv[1] == 'i') {
            is_flag = 1;
        } else {
            err_code = ERROR_CODE_INVALID_FLAG;
            return err_code;
        }
    }




    if (!is_flag) {
    
        temp = argv[1];
        while (*temp != '\0') {
            *set1_p++ = *temp++;
        }
    
        temp = argv[2];
        while (*temp != '\0') {
            *set2_p++ = *temp++;
        }

        set1_p = set1;
        set2_p = set2;

    } else {
            
        temp = argv[2];
        while (*temp != '\0') {
            *set1_p++ = *temp++;
        }
    
        temp = argv[3];
        while (*temp != '\0') {
            *set2_p++ = *temp++;
        }

        set1_p = set1;
        set2_p = set2;

    }

    /* \뒤에 지정된 문자가 오지 않을 시 오류 반환 */

    while (*set1_p != '\0') {
        if (*set1_p == '\\') {
            is_backslash = 1;
        }

        if (is_backslash) {
            ++set1_p;

            while (*escape_char_p != '\0') {
                if (*set1_p == *escape_char_p) {
                    is_escape_char = 1;
                    break;
                }

                ++escape_char_p;

            }

            escape_char_p = escape_char;
 
            if (is_escape_char) {
                is_backslash = 0;
                is_escape_char = 0;
            } else {
                err_code = ERROR_CODE_INVALID_FORMAT;
                return err_code;
            }
        }

        set1_p++;
    }

    
    set1_p = set1;
 
    while (*set1_p != '\0') {
        if (*set1_p == '\\') {
            ++set1_p;
            if (*set1_p == '\\') {
                *dummy_p = 92;
            } else if (*set1_p == 'a') {
                *dummy_p = 7;

            } else if (*set1_p == 'b') {
                *dummy_p = 8;

            } else if (*set1_p == 'f') {
                *dummy_p = 12;

            } else if (*set1_p == 'n') {
                *dummy_p = 10;

            } else if (*set1_p == 'r') {
                *dummy_p = 13;

            } else if (*set1_p == 't') {
                *dummy_p = 9;

            } else if (*set1_p == 'v') {
                *dummy_p = 11;

            } else if (*set1_p == '\'') {
                *dummy_p = 39;

            } else if (*set1_p == '\"') {
                *dummy_p = 34;
            }
            
        } else {
            *dummy_p = *set1_p;
        } 

        ++set1_p;
        ++dummy_p;
    }

    *dummy_p = '\0';

    dummy_p = dummy;
    set1_p = set1;

    

    while (*dummy_p != 0) {
        *set1_p++ = *dummy_p++;
    }

    *set1_p = '\0';

    set1_p = set1;
    dummy_p = dummy;

    printf("============\n");
    printf("set1_p's length: %d\n", strlen(set1_p));
    printf("set1_p: %s\n", set1_p);

    

    /* input.txt로 부터 한 줄씩 읽어 buffer에 저장 */

 
    while (fgets(buffer, BUFFER_LENGTH, stdin) != NULL) {
        while (*buffer_p != '\0') {
            while (*set1_p != '\0') {
                if (*buffer_p == *set1_p 
                    || (is_flag == 1 &&  (*buffer_p) == *set1_p + 32)
                    || (is_flag == 1 &&  (*buffer_p) == *set1_p - 32)) {

                    *buffer_p = *set2_p;
                }
                ++set1_p;
                ++set2_p;
            }
            buffer_p++;
            set1_p = set1;
            set2_p = set2;

        }
        printf("%s", buffer);
        buffer_p = buffer;

    }
    

    return 0;

}
