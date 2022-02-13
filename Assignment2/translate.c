#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "translate.h"

#define SET_LENGTH (512)
#define BUFFER_LENGTH (512)

int translate(int argc, const char** argv)
{ 
    char set1[SET_LENGTH] = "";
    char set2[SET_LENGTH] = "";

    char buffer[BUFFER_LENGTH] = "";
    char* buffer_p = buffer;

    char* set1_p = set1;
    char* set2_p = set2;

    const char* temp = "";


    /*                    '\','a','b', 'f', 'n', 'r', 't', 'v' ''' , '"' */
    char escape_char[] = { 92, 97, 98, 102, 110, 114, 116, 118, 39, 34, 0};

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

    /* 역슬래쉬 뒤에 지정된 문자가 오지 않으면 오류 뱉어주기 */
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
                continue;
            } else {
                err_code = ERROR_CODE_INVALID_FORMAT;
                return err_code;
            }
        }

        set1_p++;
    }
    


    set1_p = set1;
    set2_p = set2;

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
