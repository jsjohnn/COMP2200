#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "my_string.h"

int main(void)
{
    const char* one_delim = " ";
    const char* mult_delim = " ,!";
    char str_strtok[] = "IDC am a girl!";
    char str_tokenize[] = "IDC am a girl!";

    char str_strtok2[] = "!,He    am  a boy,  and    you   are a   Dirl!";
    char str_tokenize2[] = "!,He    am  a boy,  and    you   are a   Dirl!";
    char* token_strtok = strtok(str_strtok, one_delim);
    char* token_tokenize = tokenize(str_tokenize, one_delim);

     while (token_strtok != NULL &&  token_tokenize != NULL) {
        /* printf("token_strtok:%s    ", token_strtok);
        printf("token_tokenize:%s\n", token_tokenize); */

        assert(strcmp(token_strtok, token_tokenize) == 0);
        token_strtok = strtok(NULL, one_delim);
        token_tokenize = tokenize(NULL, one_delim);
    }

    token_strtok = strtok(str_strtok2, mult_delim);
    token_tokenize = tokenize(str_tokenize2, mult_delim);

    while (token_strtok != NULL && token_tokenize != NULL) {
        assert(strcmp(token_strtok, token_tokenize) == 0);
        token_strtok = strtok(NULL, mult_delim);
        token_tokenize = tokenize(NULL, mult_delim);
    }
    

}
