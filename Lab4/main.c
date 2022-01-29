#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "my_string.h"

#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    const char* one_delim = " ";
    const char* mult_delim = " ,!";
    char str_strtok[] = " D    am a boy, and you are a girl!";
    char str_tokenize[] = " D    am a boy, and you are a girl!";

    char str_strtok2[] = " ,!I    az  a boy,  and    you   are a   girl!";
    char str_tokenize2[] = " ,!I    az  a boy,  and    you   are a   girl!";
    char* token_strtok = strtok(str_strtok, one_delim);
    char* token_tokenize = tokenize(str_tokenize, one_delim);

    /* while (token_strtok != NULL && token_tokenize != NULL) {

        printf("token_tokenize:%s  ", token_tokenize);
        printf("token_strtok:%s\n", token_strtok);
       
        assert(strcmp(token_strtok, token_tokenize) == 0);
        token_strtok = strtok(NULL, one_delim);
        token_tokenize = tokenize(NULL, one_delim);
    } */

    token_strtok = strtok(str_strtok2, mult_delim);
    token_tokenize = tokenize(str_tokenize2, mult_delim);


    while (token_strtok != NULL && token_tokenize != NULL) {


        printf("token_tokenize:%s  ", token_tokenize);
        printf("token_strtok :%s\n", token_strtok);
 

        assert(strcmp(token_strtok, token_tokenize) == 0);
        token_strtok = strtok(NULL, mult_delim);
        token_tokenize = tokenize(NULL, mult_delim);
    }


    return 0;
}
