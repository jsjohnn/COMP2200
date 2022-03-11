#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "document_analyzer.h"


int main(void)
{
    load_document("input.txt");
    printf("%lu\n", get_total_word_count());
    printf("%lu\n", get_total_sentence_count());


    dispose();
    
    return 0;
}

