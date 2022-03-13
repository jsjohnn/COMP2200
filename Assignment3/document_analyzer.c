#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "document_analyzer.h"

#define LINE_LENGTH (4096)
#define INCREMENT (2)

char* g_tmp_p = NULL;
char** g_tmp_pp = NULL;
char*** g_tmp_ppp = NULL;
char**** g_tmp_pppp = NULL;

char* g_word_p = NULL;
char** g_sentence_pp = NULL;
char*** g_paragraph_ppp = NULL;
char**** g_document_pppp = NULL;

/*
char* g_f_sentence_pp = NULL;
char* g_f_paragraph_ppp = NULL;
char* g_f_document_pppp = NULL;
*/

static size_t s_para_word_cnt = 0;
static size_t s_para_sentence_cnt = 0;
static size_t s_sentence_word_cnt = 0;

static int s_is_doc = 0;

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

    if (s_is_doc == 1) {
        dispose();
    }
    
    while (fgets(line, LINE_LENGTH, stream) != NULL) {

        if (*line == '\n' || *line == '\r') {
            continue;
        }

        ++is_not_empty;

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

        while (*tmp_para_pp != NULL) {

            strcpy(tmp_line, *tmp_para_pp);
            
            token = strtok(tmp_line, " ,");

            num_count = 0;
            max_count = 0;

            while (token != NULL) {

                if (max_count == 0) {
                    g_tmp_pp = malloc((max_count + INCREMENT) * sizeof(char*));
                    g_sentence_pp = g_tmp_pp;
                    max_count += 2;
                }

                if (num_count == max_count) {
                    g_tmp_pp = realloc(g_sentence_pp, ((max_count + INCREMENT) * sizeof(char*)));
                    max_count += 2;
                    g_sentence_pp = g_tmp_pp;
                }
                

                len = strlen(token);
                g_tmp_p = malloc(len + 1);
                g_word_p = g_tmp_p;
                memcpy(g_word_p, token, len);
                g_word_p[len] = '\0';

                g_sentence_pp[num_count] = g_word_p;
                num_count += 1;

                /* delim 이 다름..*/
                /* token = strtok(NULL, " ,.!?"); */
                token = strtok(NULL, " ,");

                
            }

            if (num_count == max_count) {
                g_tmp_pp = realloc(g_sentence_pp, ((max_count + 1) * sizeof(char*)));
                max_count += 1;
                g_sentence_pp = g_tmp_pp;
                g_sentence_pp[num_count] = NULL;

            } else {
                g_sentence_pp[num_count++] = NULL;
            }

            if (par_max_count == 0) {
                g_tmp_ppp = malloc(INCREMENT * sizeof(char**));
                g_paragraph_ppp = g_tmp_ppp;
                par_max_count += INCREMENT;
            }

            if (par_max_count == par_num_count) {
                g_tmp_ppp = realloc(g_paragraph_ppp, ((par_max_count + INCREMENT) * sizeof(char**)));
                g_paragraph_ppp = g_tmp_ppp;
                par_max_count += INCREMENT;
            }

            g_paragraph_ppp[par_num_count++] = g_sentence_pp;
            tmp_para_pp++;

        }

        tmp_para_pp = tmp_tmp_pp;

        while (*tmp_para_pp != NULL) {
            free(*tmp_para_pp);
            ++tmp_para_pp;
        }

        free(tmp_tmp_pp);
        tmp_tmp_pp = NULL;

        if (par_max_count == par_num_count) {
            g_tmp_ppp = realloc(g_paragraph_ppp, ((par_max_count + 1) * sizeof(char**)));
            par_max_count += 1;
            g_paragraph_ppp = g_tmp_ppp;
            g_paragraph_ppp[par_num_count] = NULL;
        } else {
            g_paragraph_ppp[par_num_count] = NULL;
        }

        if (doc_max_count == 0) {
            g_tmp_pppp = malloc(INCREMENT * sizeof(char***));
            g_document_pppp = g_tmp_pppp;
            doc_max_count += INCREMENT;
        }

        if (doc_max_count == doc_num_count) {
            g_tmp_pppp = realloc(g_document_pppp, ((doc_max_count + INCREMENT) * sizeof(char***)));
            g_document_pppp = g_tmp_pppp;
            doc_max_count += INCREMENT;
        }

        g_document_pppp[doc_num_count++] = g_paragraph_ppp;

    }

    if (!is_not_empty) {
        dispose();
        s_is_doc = -1;

        fclose(stream);
        return TRUE;
    }

    if (doc_max_count == doc_num_count) {
        g_tmp_pppp = realloc(g_document_pppp, ((doc_max_count + 1) * sizeof(char***)));
        doc_max_count += 1;
        g_document_pppp = g_tmp_pppp;
        g_document_pppp[doc_num_count] = NULL;
    } else {
        g_document_pppp[doc_num_count] = NULL;
    }
    
    fclose(stream);

    s_is_doc = 1;

    return TRUE;
}

void dispose(void)
{
    size_t word_cnt;
    size_t para_cnt;

    if (s_is_doc < 1) {
        return;
    }

    while (*g_document_pppp != NULL) {
        para_cnt = 0;

        while (**g_document_pppp != NULL) {
            word_cnt = 0;

            while (***g_document_pppp != NULL) {
                ++word_cnt;
                free(***g_document_pppp);
                (**g_document_pppp)++;
            }
            free(**g_document_pppp - word_cnt);
            (*g_document_pppp)++;
            ++para_cnt;

        }
        free(*g_document_pppp - para_cnt);

        g_document_pppp++;
    }

    free(g_tmp_pppp);
    s_is_doc = 0;

}

size_t get_total_word_count(void)
{

    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_word_cnt = 0;

    if (s_is_doc < 1) {
        return 0;
    }

    while (*g_document_pppp != NULL) {
        para_cnt = 0;

        while (**g_document_pppp != NULL) {
            word_cnt = 0;

            while (***g_document_pppp != NULL) {
                ++weighted_word_cnt;
                ++word_cnt;
                (**g_document_pppp)++;
            }
            **g_document_pppp -= word_cnt;
            (*g_document_pppp)++;
            ++para_cnt;

        }
        *g_document_pppp -= para_cnt;

        g_document_pppp++;
    }

    g_document_pppp = g_tmp_pppp;

    return weighted_word_cnt;

}

size_t get_total_sentence_count(void)
{
    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_sen_cnt = 0;

    if (s_is_doc < 1) {
        return 0;
    }

    while (*g_document_pppp != NULL) {
        para_cnt = 0;

        while (**g_document_pppp != NULL) {
            word_cnt = 0;

            while (***g_document_pppp != NULL) {
                ++word_cnt;
                (**g_document_pppp)++;
            }
            ++weighted_sen_cnt;

            **g_document_pppp -= word_cnt;
            (*g_document_pppp)++;
            ++para_cnt;

        }
        *g_document_pppp -= para_cnt;

        g_document_pppp++;
    }

    g_document_pppp = g_tmp_pppp;

    return weighted_sen_cnt;

}

size_t get_total_paragraph_count(void)
{
    size_t word_cnt;
    size_t para_cnt;
    size_t weighted_para_cnt = 0;

    if (s_is_doc < 1) {
        return 0;
    }

    while (*g_document_pppp != NULL) {
        para_cnt = 0;
        ++weighted_para_cnt;

        while (**g_document_pppp != NULL) {
            word_cnt = 0;

            while (***g_document_pppp != NULL) {
                ++word_cnt;
                (**g_document_pppp)++;
            }
            **g_document_pppp -= word_cnt;
            (*g_document_pppp)++;
            ++para_cnt;

        }
        *g_document_pppp -= para_cnt;

        g_document_pppp++;
    }

    g_document_pppp = g_tmp_pppp;

    return weighted_para_cnt;

}

const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    size_t i = 0;
    const char*** para_ppp = NULL;

    size_t sen_cnt = 0;
    size_t word_cnt = 0;

    size_t total_paragraph_count = get_total_paragraph_count();
    if (s_is_doc < 1 || paragraph_index > total_paragraph_count - 1) {
        return NULL;
    }

    while (*g_document_pppp != NULL) {
        if (i == paragraph_index) {
            para_ppp = (const char***)*g_document_pppp;
            break;
        }

        ++g_document_pppp;
        ++i;
    }

    s_para_word_cnt = 0;

    while (**g_document_pppp != NULL) {
        ++sen_cnt;
        word_cnt = 0;
        while (***g_document_pppp != NULL) {
            ++s_para_word_cnt;

            ++word_cnt;
            ++(**g_document_pppp);
        }
        **g_document_pppp -= word_cnt;
        ++(*g_document_pppp);
    }
    *g_document_pppp -= sen_cnt;

    g_document_pppp = g_tmp_pppp;

    s_para_sentence_cnt = sen_cnt;

    return para_ppp;
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    const char*** tmp = paragraph;
    tmp = NULL;
    assert(tmp == NULL);

    return s_para_word_cnt;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    const char*** tmp = paragraph;
    tmp = NULL;
    assert(tmp == NULL);

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
    assert(tmp == NULL);

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

    if (s_is_doc < 1) {
        return FALSE;
    }

    stream = fopen(filename, "wb");

    while (*g_document_pppp != NULL) {
        fprintf(stream, "Paragraph %d:\n", para_count++);
        para_cnt = 0;
        
        sen_count = 0;
        while (**g_document_pppp != NULL) {
            word_cnt = 0;
            fprintf(stream, "    Sentence %d:\n", sen_count++);

            while (***g_document_pppp != NULL) {
                fprintf(stream, "        %s", ***g_document_pppp);
                ++word_cnt;
                (**g_document_pppp)++;

                if (***g_document_pppp != NULL) {
                    fprintf(stream, "\n");
                }
            }
            **g_document_pppp -= word_cnt;

            (*g_document_pppp)++;
            ++para_cnt;
            if (**g_document_pppp != NULL) {
                fprintf(stream, "\n");
            }

        }
        *g_document_pppp -= para_cnt;

        g_document_pppp++;

        if (*g_document_pppp != NULL) {
            fprintf(stream, "\n\n");
        }
    }

    g_document_pppp = g_tmp_pppp;

    fclose(stream);

    return TRUE;
    
}
