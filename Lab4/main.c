#include <stdio.h>
#include <string.h>
#include "my_string.h"
 
int main(void)
{
    size_t i;
    char* token;
    char str[] = "ab cd ef";
    char str2[] = "bb cc dd";
    char str3[] = "gg pp mm";

    token = tokenize(str, " ");
    token = strtok(str2, " ");
    token = strtok(NULL, " ");
    token = tokenize(str3, " ");
    printf("token:%s\n", token);
    
}
