#include "translate.h"
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[])
{

    printf("=======\n");
    printf("%s\n", argv[1]);

    return translate(argc, argv);
}
