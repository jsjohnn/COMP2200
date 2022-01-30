#include <stdio.h>
#include <string.h>
#include "my_string.h"
 
int main(void)
{
    size_t i;
    char* token;
    char str[] = "ab cd ef";
    char str2[] = "bb cc dd";
    char str3[] = "bb cc dd";

    token = tokenize(str, " ");
    token = strtok(str2, " ");
    /* token = strtok(NULL, " "); */
    printf("token: %s\n", token);
    
}
