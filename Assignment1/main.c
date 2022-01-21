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
/* hori */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);
    place_stone(COLOR_BLACK, 0, 5);
    place_stone(COLOR_BLACK, 0, 6);

    assert(6 == get_score(COLOR_BLACK));

    insert_column(COLOR_BLACK, 20);
    view_ary();


    assert(3 == get_score(COLOR_BLACK));

    assert(15 == get_row_count());
    assert(16 == get_column_count());

    view_ary();
}


