#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "document_analyzer.h"

#define LINE_LENGTH (4096)
#define INCREMENT (2)

char* tmp_p = NULL;
char** tmp_pp = NULL;
char*** tmp_ppp = NULL;
char**** tmp_pppp = NULL;

char* word_p = NULL;
char** sentence_pp = NULL;
char*** paragraph_ppp = NULL;
char**** document_pppp = NULL;

char* f_sentence_pp = NULL;
char* f_paragraph_ppp = NULL;
char* f_document_pppp = NULL;

static size_t is_doc = 0;


int load_document(const char* document)
{
    size_t num_count;
    size_t max_count;

    size_t par_num_count = 0;
    size_t par_max_count = 0;

    size_t doc_num_count = 0;
    size_t doc_max_count = 0;

    size_t len;

    char line[LINE_LENGTH];
    char tmp_line[LINE_LENGTH];


    /* temp paragrap, 이 함수 안에서 해제 */
    char** tmp_para_pp = NULL;
    char** tmp_tmp_pp = NULL;

    char* tmp_sen_p = NULL;
    char* tmp_tmp_p = NULL;

    size_t tmp_num_count;
    size_t tmp_max_count;
    
    char* token = NULL;

    FILE* stream;

    stream = fopen(document, "rb");

    
    while (fgets(line, LINE_LENGTH, stream) != NULL) {

        /* 읽은 줄이 단순히 '\n'인 경우, 다음 줄로 이동 */
        if (*line == '\n') {
            continue;
        }

        /* printf("%s", line); */

        tmp_num_count = 0;
        tmp_max_count = 0;

        par_num_count = 0;
        par_max_count = 0;

        strcpy(tmp_line, line);

        tmp_tmp_pp = malloc(2 * sizeof(char*));
        tmp_para_pp = tmp_tmp_pp;
        tmp_max_count += 2;


        token = strtok(tmp_line, ".!?");

        while (token != NULL) {

/* 마지막 토큰이 \n 인 경우 반복문을 빠져 나감 */
            if (*token == '\n') {
                break;
            }


            if (tmp_num_count == tmp_max_count) {
                tmp_tmp_pp = realloc(tmp_para_pp, ((tmp_max_count + INCREMENT) * sizeof(char*)));
                tmp_max_count += 2;
                tmp_para_pp = tmp_tmp_pp;
            }

            len = strlen(token);
            tmp_tmp_p = malloc(len + 1);
            tmp_sen_p = tmp_tmp_p;
            memcpy(tmp_sen_p, token, len);
            tmp_sen_p[len] = '\0';
 
            tmp_para_pp[tmp_num_count] = tmp_sen_p;
            ++tmp_num_count;
            
            token = strtok(NULL, ".!?");

        }

        if (tmp_num_count == tmp_max_count) {
            tmp_tmp_pp = realloc(tmp_para_pp, ((tmp_max_count + 1) * sizeof(char*)));
            tmp_max_count += 1;
            tmp_para_pp = tmp_tmp_pp;
            tmp_para_pp[tmp_num_count] = NULL;
        } else {
            tmp_para_pp[tmp_num_count] = NULL;
        }

        assert(tmp_para_pp == tmp_tmp_pp);

        while (*tmp_para_pp != NULL) {

            strcpy(tmp_line, *tmp_para_pp);
            
            token = strtok(tmp_line, " ,");

            num_count = 0;
            max_count = 0;

            while (token != NULL) {

                if (max_count == 0) {
                    tmp_pp = malloc((max_count + INCREMENT) * sizeof(char*));
                    sentence_pp = tmp_pp;
                    max_count += 2;
                }

                if (num_count == max_count) {
                    tmp_pp = realloc(sentence_pp, ((max_count + INCREMENT) * sizeof(char*)));
                    max_count += 2;
                    sentence_pp = tmp_pp;
                }

                len = strlen(token);
                tmp_p = malloc(len + 1);
                word_p = tmp_p;
                memcpy(word_p, token, len);
                word_p[len] = '\0';

                sentence_pp[num_count] = word_p;
                num_count += 1;
            
                token = strtok(NULL, " ,.!?");
                
            }

            if (num_count == max_count) {
                tmp_pp = realloc(tmp_pp, ((max_count + 1) * sizeof(char*)));
                max_count += 1;
                sentence_pp = tmp_pp;
                sentence_pp[num_count] = NULL;

            } else {
                sentence_pp[num_count] = NULL;
            }

            if (par_max_count == 0) {
                tmp_ppp = malloc(INCREMENT * sizeof(char**));
                paragraph_ppp = tmp_ppp;
                par_max_count += INCREMENT;
            }

            if (par_max_count == par_num_count) {
                tmp_ppp = realloc(paragraph_ppp, ((par_max_count + INCREMENT) * sizeof(char**)));
                paragraph_ppp = tmp_ppp;
                par_max_count += INCREMENT;
            }
/*
            if (par_num_count == 0) {
                f_paragraph_ppp = sentence_pp;
            }
*/

            paragraph_ppp[par_num_count++] = sentence_pp;

            tmp_para_pp++;

        }


        if (par_max_count == par_num_count) {
            tmp_ppp = realloc(tmp_ppp, ((par_max_count + 1) * sizeof(char**)));
            par_max_count += 1;
            paragraph_ppp = tmp_ppp;
            paragraph_ppp[par_num_count] = NULL;
        } else {
            paragraph_ppp[par_num_count] = NULL;
        }

        if (doc_max_count == 0) {
            tmp_pppp = malloc(INCREMENT * sizeof(char***));
            document_pppp = tmp_pppp;
            doc_max_count += INCREMENT;
        }

        if (doc_max_count == doc_num_count) {
            tmp_pppp = realloc(document_pppp, ((doc_max_count  + INCREMENT) * sizeof(char***)));
            document_pppp = tmp_pppp;
            doc_max_count += INCREMENT;
        }

        document_pppp[doc_num_count++] = paragraph_ppp;
        
        while (*tmp_tmp_pp != NULL) {
            free(*tmp_tmp_pp++);
        }

        tmp_tmp_p = NULL;
        tmp_tmp_pp = NULL;


    /* 반복문 끝 */
    }

    if (doc_max_count == doc_num_count) {
        tmp_pppp = realloc(tmp_pppp, ((doc_max_count + 1) * sizeof(char**)));
        doc_max_count += 1;
        document_pppp = tmp_pppp;
        document_pppp[doc_num_count] = NULL;
    } else {
        document_pppp[doc_num_count] = NULL;
    }


#if 0
    printf("%s\n", document_pppp[0][0][0]);
    printf("%s\n", document_pppp[0][0][1]);
    printf("%s\n", document_pppp[0][0][2]);
    printf("%s\n", document_pppp[0][0][3]);
    printf("%s\n", document_pppp[0][0][4]);
    printf("%s\n", document_pppp[0][0][5]);
    printf("%s\n", document_pppp[0][0][6]);

    puts("=======");

    printf("%s\n", document_pppp[0][1][0]);
    printf("%s\n", document_pppp[0][1][1]);
    printf("%s\n", document_pppp[0][1][2]);
    printf("%s\n", document_pppp[0][1][3]);

    puts("=======");

    printf("%s\n", document_pppp[0][2][0]);
    printf("%s\n", document_pppp[0][2][1]);
    printf("%s\n", document_pppp[0][2][2]);
    printf("%s\n", document_pppp[0][2][3]);
    printf("%s\n", document_pppp[0][2][4]);


    puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");

    printf("%s\n", document_pppp[1][0][0]);
    printf("%s\n", document_pppp[1][0][1]);
    printf("%s\n", document_pppp[1][0][2]);
    printf("%s\n", document_pppp[1][0][3]);
    printf("%s\n", document_pppp[1][0][4]);
    printf("%s\n", document_pppp[1][0][5]);

    puts("=======");

    printf("%s\n", document_pppp[1][1][0]);
    printf("%s\n", document_pppp[1][1][1]);
    printf("%s\n", document_pppp[1][1][2]);
    printf("%s\n", document_pppp[1][1][3]);
    printf("%s\n", document_pppp[1][1][4]);
    printf("%s\n", document_pppp[1][1][5]);
    printf("%s\n", document_pppp[1][1][6]);
    printf("%s\n", document_pppp[1][1][7]);
    printf("%s\n", document_pppp[1][1][8]);
    printf("%s\n", document_pppp[1][1][9]);


    puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");

    printf("%s\n", document_pppp[2][0][0]);
    printf("%s\n", document_pppp[2][0][1]);
    printf("%s\n", document_pppp[2][0][2]);
    printf("%s\n", document_pppp[2][0][3]);

#endif
    
    fclose(stream);

    is_doc = 1;
    return TRUE;

    
}

/*

char* tmp_p = NULL;
char** tmp_pp = NULL;
char*** tmp_ppp = NULL;
char**** tmp_pppp = NULL;

*/

void dispose(void)
{

/* word free */
    while (*tmp_pppp != NULL) {
        while (**tmp_pppp != NULL) {
            while (***tmp_pppp != NULL) {
                free(***tmp_pppp);
                ++(**tmp_pppp);
            }
            ++(*tmp_pppp);
            
        }
        ++tmp_pppp;
    }

    tmp_pppp = document_pppp;


#if 0

/* sentance free - not working... */

/*
    while (*tmp_pppp != NULL) {
        while (**tmp_pppp != NULL) {
            puts("===");
            free(**tmp_pppp);
            ++(*tmp_pppp);
        }
        
        ++tmp_pppp;
    }

    tmp_pppp = document_pppp;
*/


#endif

}

/* TODO: loading 된 문서가 없는 경우 0을 반환하도록 수정 */
size_t get_total_word_count(void)
{
    size_t word_count = 0;

    while (*tmp_pppp != NULL) {
        while (**tmp_pppp != NULL) {
            while (***tmp_pppp != NULL) {
                ++word_count;
                ++(**tmp_pppp);
            }
            ++(*tmp_pppp);
            
        }
        ++tmp_pppp;
    }

    tmp_pppp = document_pppp;

    printf("%s\n", ***tmp_pppp);
    printf("%s\n", ***document_pppp);

    

    return word_count;
}

size_t get_total_sentence_count(void)
{
    size_t sentence_count = 0;
    size_t num = 0;

/* for debug */

    printf("%s\n", *sentence_pp);
    printf("%s\n", *(sentence_pp + 1));

    puts("======");

    printf(": %s\n", ***tmp_pppp);



/* for debug */

    while (*tmp_pppp != NULL) {
        ++num;
        while (**tmp_pppp != NULL) {
            while (***tmp_pppp != NULL) {
                ++(**tmp_pppp);
            }
            ++(*tmp_pppp);
            
        }
        ++tmp_pppp;
    }

    printf("num: %lu\n", num);

    return sentence_count;
    
}
