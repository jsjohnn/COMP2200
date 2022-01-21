#include <stdio.h>
#include <assert.h>
#include "pomoku.h"

void init_game_and_test(void)
{
    init_game();
 
    assert(15 == get_row_count());
    assert(15 == get_column_count());
 
    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}

int main(void)
{
    init_game_and_test();
    view_ary();
}


