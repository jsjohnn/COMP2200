#include <stdio.h>
#include <limits.h>
#include "pomoku.h"

int g_black_score = 0;
int g_white_score = 0;
int g_boards[20][20] = {0,};

/* 2.2 */
void init_game(void)
{
    size_t i;
    size_t j;

    for (i = 15; i < 20; ++i) {
        for (j =0; j < 20; ++j) {
            g_boards[i][j] = -1;
            g_boards[j][i] = -1;
        }
    }
    
/* debug start */

    for (i = 0; i < 15; ++i) {
        g_boards[14][i] = -1;
    }

/* debug end */

    g_black_score = 0;
    g_white_score = 0;
    
}

/* 2.3 */
size_t get_row_count(void)
{
    size_t i;
    
    for (i = 0; i < 20; ++i) {
        if (g_boards[i][0] == -1) {
            break;
        }
    }
    return i;
}

/* 2.4 */
size_t get_column_count(void)
{
    size_t i;
    
    for (i = 0; i < 20; ++i) {
        if (g_boards[0][i] == -1) {
            break;
        }
    }
    return i;
}

/* 2.5 */
int get_score(const color_t color)
{
    size_t temps_score;
    size_t weighted_score;
    size_t add_score;
    size_t i;
    size_t j;
    int m;
    int n;

    size_t row_count = get_row_count();
    size_t column_count = get_column_count();

    weighted_score = 0;

    if (color != COLOR_BLACK && color != COLOR_WHITE) {
        return -1;
    }

/* 가로 */
    for (i = 0; i < row_count; ++i) {
        temps_score = 0;
        add_score = 0;

        for (j = 0; j < column_count; ++j) {
        /* printf("boards[%d][%d]\n",m+n, n); */
            if (g_boards[i][j] == (int)color) {
                temps_score += g_boards[i][j];

                if (color == COLOR_BLACK && temps_score >= 5) {
                    add_score += 1;
                    weighted_score += add_score;
                } else if (color == COLOR_WHITE && temps_score >= 10) {
                    add_score += 1;
                    weighted_score += add_score;
                }
            } else {
                temps_score = 0;
                add_score = 0;
            }
            
        }
        /* printf("=================\n"); */
    }
    
/* 세로 */
    for (i = 0; i < row_count; ++i) {
        temps_score = 0;
        add_score = 0;

        for (j = 0; j < column_count; ++j) {
        /* printf("boards[%d][%d]\n",m+n, n); */
            if (g_boards[j][i] == (int)color) {
                temps_score += g_boards[j][i];

                if (color == COLOR_BLACK && temps_score >= 5) {
                    add_score += 1;
                    weighted_score += add_score;
                } else if (color == COLOR_WHITE && temps_score >= 10) {
                    add_score += 1;
                    weighted_score += add_score;
                }
            } else {
                temps_score = 0;
                add_score = 0;
            }
            
        }
        /* printf("=================\n"); */
    }

/* 대각선 ↘︎ 왼쪽*/
    for (m = row_count - 5; m >= 0; --m) {
        temps_score = 0;
        add_score = 0;

        for (n = 0; n < (int)row_count - m; ++n) {
            /* printf("boards[%d][%d]\n",m+n, n); */
            if (g_boards[m + n][n] == (int)color) {
                temps_score += g_boards[m + n][n];

                if (color == COLOR_BLACK && temps_score >= 5) {
                    add_score += 1;
                    weighted_score += add_score;
                } else if (color == COLOR_WHITE && temps_score >= 10) {
                    add_score += 1;
                    weighted_score += add_score;
                }
            } else {
                temps_score = 0;
                add_score = 0;
            }
        }
        /* printf("=================\n"); */
    }

/* 대각선 ↘︎ 오른쪽*/
    for (m = row_count - 5; m > 0; --m) {
        temps_score = 0;
        add_score = 0;

        for (n = 0; n < (int)row_count - m; ++n) {
            /* printf("boards[%d][%d]\n",n, m + n); */
            if (g_boards[n][m + n] == (int)color) {
                temps_score += g_boards[n][m + n];

                if (color == COLOR_BLACK && temps_score >= 5) {
                    add_score += 1;
                    weighted_score += add_score;
                } else if (color == COLOR_WHITE && temps_score >= 10) {
                    add_score += 1;
                    weighted_score += add_score;
                }
            } else {
                temps_score = 0;
                add_score = 0;
            }
        }
        /* printf("=================\n"); */
    }

/* 대각선 ↗︎　왼쪽 */
    for (m = 4; m < (int)row_count; ++m) {
        temps_score = 0;
        add_score = 0;

        for (n = 0; n < m + 1; ++n) {
            if (g_boards[m - n][n] == -1) {
                break;
            }
            printf("boards[%d][%d]\n",m - n, n);
            if (g_boards[m - n][n] == (int)color) {
                temps_score += g_boards[m - n][n];

                if (color == COLOR_BLACK && temps_score >= 5) {
                    add_score += 1;
                    weighted_score += add_score;
                } else if (color == COLOR_WHITE && temps_score >= 10) {
                    add_score += 1;
                    weighted_score += add_score;
                }
            } else {
                temps_score = 0;
                add_score = 0;
            }
        }
        printf("=================\n");

    }

/* 대각선 ↗︎ 오른쪽 */
    

/* 합산 */

    if (color == COLOR_BLACK) {
        g_black_score = weighted_score;
    } else {
        g_white_score = weighted_score;
    }

    return weighted_score;
}

/* 2.6 */
int get_color(const size_t row, const size_t col)
{
    if (g_boards[row][col] == 1) {
        return 0;
    } else if (g_boards[row][col] == 2) {
        return 1;
    } else {
        return -1;
    }
}

/* 2.7 */
int is_placeable(const size_t row, const size_t col)
{
    if (g_boards[row][col] == 0) {
        return TRUE;
    }

    return FALSE;
}

/* 2.8 */
int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (is_placeable(row, col) == TRUE) {
        g_boards[row][col] = color;
        return TRUE;
    }

    return FALSE;
}


void view_ary(void)
{
    size_t i;
    size_t j;

    for (i = 0; i < 20; ++i) {
        for ( j = 0; j < 20; ++j) {
            printf("%2d",g_boards[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}
