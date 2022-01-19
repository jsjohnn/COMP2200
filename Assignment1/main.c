#include <stdio.h>
#include "pomoku.h"

int main(void)
{
    int a;
    int b;

    init_game();
    printf("row_count: %lu\n",get_row_count()); /* 15 */
    printf("column_count: %lu\n",get_column_count()); /* 15 */
    printf("get_color: %d\n", get_color(0,0)); /* -1 */

    a = place_stone(COLOR_BLACK, 3, 5); /* TRUE (1) */
    b = place_stone(COLOR_BLACK, 3, 5); /* FALSE (0) */

    place_stone(COLOR_WHITE, 14, 14);
    
    printf("=======================\n");
    printf("%d\n",a);
    printf("%d\n",b);

    place_stone(COLOR_BLACK, 3, 1);
    place_stone(COLOR_BLACK, 3, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 3, 4);
    place_stone(COLOR_BLACK, 3, 5); /* 1 */
    place_stone(COLOR_BLACK, 3, 6); /* 3 */
    place_stone(COLOR_BLACK, 3, 7); /* 6 */
    place_stone(COLOR_BLACK, 3, 8); /* 10 */
    place_stone(COLOR_BLACK, 3, 9); /* 15 */
    place_stone(COLOR_BLACK, 3, 10); /* 21 */
    place_stone(COLOR_BLACK, 3, 11); /* 28 */
    place_stone(COLOR_BLACK, 3, 12); /* 36 */

    place_stone(COLOR_BLACK, 4, 2); /* 36 */
    place_stone(COLOR_BLACK, 5, 3); /* 36 */
    place_stone(COLOR_BLACK, 6, 4); /* 36 */
    place_stone(COLOR_BLACK, 7, 5); /* 36 */
    place_stone(COLOR_BLACK, 8, 6); /* 36 */


    place_stone(COLOR_WHITE, 9, 0);
    place_stone(COLOR_WHITE, 8, 1);
    place_stone(COLOR_WHITE, 7, 2);
    place_stone(COLOR_WHITE, 6, 3);
    place_stone(COLOR_WHITE, 5, 4);
    place_stone(COLOR_WHITE, 4, 5);
    place_stone(COLOR_WHITE, 3, 6);



    printf("black score: %d\n",get_score(COLOR_BLACK));
    printf("white score: %d\n",get_score(COLOR_WHITE));

    view_ary(); 

}
