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

static size_t s_para_word_cnt = 0;
static size_t s_para_sentence_cnt = 0;
static size_t s_sentence_word_cnt = 0;


static int is_doc = 0;

int load_document(const char* document)
{
    size_t num_count;
    size_t max_count;

    size_t par_num_count;
    size_t par_max_count;

    size_t doc_num_count = 0;
    size_t doc_max_count = 0;

    size_t len;

    size_t is_not_empty = 0;

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

    if (!stream) {
        return FALSE;
    }

    if (is_doc == 1) {
        dispose();
    }
    
    while (fgets(line, LINE_LENGTH, stream) != NULL) {
/*        
        if (*line == '\0') {
            dispose();
            is_doc = -1;

            fclose(stream);
            return TRUE;
            
        }
*/

        if (*line == '\n' || *line == '\r') {
            continue;
        }

        ++is_not_empty;

        tmp_num_count = 0;
        tmp_max_count = 0;

        par_num_count = 0;
        par_max_count = 0;

        /* 굳이 복사 안해도..? */
        strcpy(tmp_line, line);

        tmp_tmp_pp = malloc(2 * sizeof(char*));
        tmp_para_pp = tmp_tmp_pp;
        tmp_max_count += 2;

        token = strtok(tmp_line, ".!?");

        while (token != NULL) {

            if (*token == '\n' || *token == '\r') {
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
            tmp_para_pp[tmp_num_count++] = NULL;
        }

#if 0
        while (*tmp_para_pp != NULL) {
            printf("%s\n", *tmp_para_pp++);
        }
        fclose(stream);
        assert(1==8);
#endif

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

                /* delim 이 다름..*/
                /* token = strtok(NULL, " ,.!?"); */
                token = strtok(NULL, " ,");

                
            }

            if (num_count == max_count) {
                tmp_pp = realloc(sentence_pp, ((max_count + 1) * sizeof(char*)));
                max_count += 1;
                sentence_pp = tmp_pp;
                sentence_pp[num_count] = NULL;

            } else {
                sentence_pp[num_count++] = NULL;
            }

#if 0

            while (*sentence_pp != NULL) {
                printf("%s\n", *sentence_pp++);
            }

            fclose(stream);
            assert(0 == 1);
#endif

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

            paragraph_ppp[par_num_count++] = sentence_pp;
            tmp_para_pp++;

        }

        tmp_para_pp = tmp_tmp_pp;
        assert(tmp_tmp_pp == tmp_para_pp);

        while (*tmp_para_pp != NULL) {
            free(*tmp_para_pp);
            ++tmp_para_pp;
        }

        free(tmp_tmp_pp);
        tmp_tmp_pp = NULL;

        if (par_max_count == par_num_count) {
            tmp_ppp = realloc(paragraph_ppp, ((par_max_count + 1) * sizeof(char**)));
            par_max_count += 1;
            paragraph_ppp = tmp_ppp;
            paragraph_ppp[par_num_count] = NULL;
        } else {
            paragraph_ppp[par_num_count] = NULL;
        }

#if 0

        while (*paragraph_ppp != NULL) {
            while (**paragraph_ppp != NULL) {
                printf("%s\n", **paragraph_ppp);
                (*paragraph_ppp)++;
            }
            puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
            paragraph_ppp++;

        }

        fclose(stream);
        assert(1 == 9);

#endif

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

    }

    if(!is_not_empty) {
        dispose();
        is_doc = -1;

        fclose(stream);
        return TRUE;
    }

    if (doc_max_count == doc_num_count) {
        tmp_pppp = realloc(document_pppp, ((doc_max_count + 1) * sizeof(char***)));
        doc_max_count += 1;
        document_pppp = tmp_pppp;
        document_pppp[doc_num_count] = NULL;
    } else {
        document_pppp[doc_num_count] = NULL;
    }
    
    fclose(stream);

    is_doc = 1;

    return TRUE;
}

void dispose(void)
{
    size_t word_cnt;
    size_t para_cnt;

    assert(document_pppp == tmp_pppp);

    if (is_doc < 1) {
        return;
    }

    while (*document_pppp != NULL) {
        para_cnt = 0;

        while (**document_pppp != NULL) {
            word_cnt = 0;

            while (***document_pppp != NULL) {
                ++word_cnt;
                free(***document_pppp);
                (**document_pppp)++;
            }
            free(**document_pppp - word_cnt);
            (*document_pppp)++;
            ++para_cnt;

        }
        free(*document_pppp - para_cnt);

        document_pppp++;
    }

    free(tmp_pppp);
    is_doc = 0;

}

size_t get_total_word_count(void)
{

    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_word_cnt = 0;

    assert(document_pppp == tmp_pppp);
    if (is_doc < 1) {
        return 0;
    }

    while (*document_pppp != NULL) {
        para_cnt = 0;

        while (**document_pppp != NULL) {
            word_cnt = 0;

            while (***document_pppp != NULL) {
                ++weighted_word_cnt;
                ++word_cnt;
                (**document_pppp)++;
            }
            **document_pppp -= word_cnt;
            (*document_pppp)++;
            ++para_cnt;

        }
        *document_pppp -= para_cnt;

        document_pppp++;
    }

    document_pppp = tmp_pppp;

    return weighted_word_cnt;

}

size_t get_total_sentence_count(void)
{
    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_sen_cnt = 0;

    assert(document_pppp == tmp_pppp);

    if (is_doc < 1) {
        return 0;
    }

    while (*document_pppp != NULL) {
        para_cnt = 0;

        while (**document_pppp != NULL) {
            word_cnt = 0;

            while (***document_pppp != NULL) {
                ++word_cnt;
                (**document_pppp)++;
            }
            ++weighted_sen_cnt;

            **document_pppp -= word_cnt;
            (*document_pppp)++;
            ++para_cnt;

        }
        *document_pppp -= para_cnt;

        document_pppp++;
    }

    document_pppp = tmp_pppp;

    return weighted_sen_cnt;

}

size_t get_total_paragraph_count(void)
{
    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_para_cnt = 0;

    assert(document_pppp == tmp_pppp);

    if (is_doc < 1) {
        return 0;
    }

    while (*document_pppp != NULL) {
        para_cnt = 0;
        ++weighted_para_cnt;

        while (**document_pppp != NULL) {
            word_cnt = 0;

            while (***document_pppp != NULL) {
                ++word_cnt;
                (**document_pppp)++;
            }
            **document_pppp -= word_cnt;
            (*document_pppp)++;
            ++para_cnt;

        }
        *document_pppp -= para_cnt;

        document_pppp++;
    }

    document_pppp = tmp_pppp;

    return weighted_para_cnt;

}

const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    size_t i = 0;
    const char*** para_ppp = NULL;

    size_t sen_cnt = 0;
    size_t word_cnt = 0;

    size_t total_paragraph_count = get_total_paragraph_count();
    if (is_doc < 1 || paragraph_index  > total_paragraph_count - 1 ) {
        return NULL;
    }

    while (*document_pppp != NULL) {
        if (i == paragraph_index) {
             para_ppp = (const char***)*document_pppp;
             break;
        }

        ++document_pppp;
        ++i;
    }

    s_para_word_cnt = 0;

    while (**document_pppp != NULL) {
        ++sen_cnt;
        word_cnt = 0;
        while (***document_pppp != NULL) {
            ++s_para_word_cnt;

            ++word_cnt;
            ++(**document_pppp);
        }
        **document_pppp -= word_cnt;
        ++(*document_pppp);
    }
    *document_pppp -= sen_cnt;

    document_pppp = tmp_pppp;

    s_para_sentence_cnt = sen_cnt;

    return para_ppp;
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    const char*** tmp = paragraph;
    tmp = NULL;

    return s_para_word_cnt;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    const char*** tmp = paragraph;
    tmp = NULL;

    return s_para_sentence_cnt;
}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{
    const char*** para_ppp;
    const char** sen_pp = NULL;

    size_t total_para_cnt = 0;

    size_t i = 0;
    size_t tmp_sen_cnt = 0;
    size_t tmp_word_cnt = 0;

    total_para_cnt = get_total_paragraph_count();

    if (total_para_cnt == 0 || paragraph_index > (size_t)(total_para_cnt - 1)) {
        
        return NULL;
    }
    para_ppp = get_paragraph_or_null(paragraph_index);

    assert(para_ppp != NULL);

    if (sentence_index > (size_t)(s_para_sentence_cnt - 1)) {
        return NULL;
    }

    s_sentence_word_cnt = 0;

    while (*para_ppp != NULL) {
        tmp_sen_cnt++;
        if (i == sentence_index) {
            sen_pp = (const char**)*para_ppp;

            while (**para_ppp != NULL) {
                ++tmp_word_cnt;
                ++s_sentence_word_cnt;

                ++(*para_ppp);
            }

            *para_ppp -= tmp_word_cnt;
            break;
        }

        ++para_ppp;
        ++i;
    }
    para_ppp -= tmp_sen_cnt;
    
    

    return sen_pp;
}


size_t get_sentence_word_count(const char** sentence)
{
    const char** tmp = sentence;
    tmp = NULL;

    if (sentence == NULL) {
        return 0;
    }
    return s_sentence_word_cnt;
}

int print_as_tree(const char* filename)
{
    size_t para_count = 0;
    size_t sen_count;

    size_t word_cnt;
    size_t para_cnt;

    FILE* stream;

    if (is_doc < 1) {
        return FALSE;
    }

    stream = fopen(filename, "wb");

    assert(tmp_pppp == document_pppp);

    while (*document_pppp != NULL) {
        fprintf(stream, "Paragraph %lu:\n", para_count++);
        para_cnt = 0;
        
        sen_count = 0;
        while (**document_pppp != NULL) {
            word_cnt = 0;
            fprintf(stream, "    Sentence %lu:\n", sen_count++);

            while (***document_pppp != NULL) {
                fprintf(stream, "        %s\n", ***document_pppp);
                ++word_cnt;
                (**document_pppp)++;
            }
            **document_pppp -= word_cnt;

            (*document_pppp)++;
            ++para_cnt;

        }
        *document_pppp -= para_cnt;

        document_pppp++;

        if (*document_pppp != NULL) {
            fprintf(stream, "\n");
        }
    }

    document_pppp = tmp_pppp;

    fclose(stream);

    return TRUE;
    
}
