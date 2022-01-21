#include <stdio.h>
#include <limits.h>
#include "pomoku.h"

#define ROW_LENGTH (20)
#define COLUMN_LENGTH (20)
#define BLANK (7)

int g_black_score = 0;
int g_white_score = 0;
int g_boards[20][20];

/* 2.2 */
void init_game(void)
{
    size_t i;
    size_t j;

    g_black_score = 0;
    g_white_score = 0;

    for (i = 0; i < ROW_LENGTH; ++i) {
        for (j = 0; j < COLUMN_LENGTH; ++j) {
            g_boards[i][j] = -1;
        }
    }

    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 15; ++j) {
            g_boards[i][j] = BLANK;
        }

    }

}

/* 2.3 */
size_t get_row_count(void)
{
    size_t i;

    for (i = 0; i < ROW_LENGTH; ++i) {
        if (g_boards[i][0] == -1) {
            return i;
        }
    }

    return 0;
}

/* 2.4 */
size_t get_column_count(void)
{
    size_t i;

    for (i = 0; i < COLUMN_LENGTH; ++i) {
        if (g_boards[0][i] == -1) {
            return i;
        }
    }
   return 0;
}

/* 2.5 */
int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        return g_black_score;
    case COLOR_WHITE:
        return g_white_score;
    default:
        return -1;
    }
}

/* 2.6 */
int get_color(const size_t row, const size_t col)
{
    if (row < 0 || row > get_row_count() - 1 || col < 0 
        || col > get_column_count() - 1) {
        return -1;
    }

    switch ((color_t)g_boards[row][col]) {
    case COLOR_BLACK:
        return COLOR_BLACK;
    case COLOR_WHITE:
        return COLOR_WHITE;
    default:
        return -1;
    }
}

/* 2.7 */
int is_placeable(const size_t row, const size_t col)
{
    if (row < 0 || row > get_row_count() - 1 || col < 0 
        || col > get_column_count() - 1 || g_boards[row][col] != BLANK) {
        return FALSE;
    }  
    
    return TRUE;
}

/* 2.8 */
int place_stone(const color_t color, const size_t row, const size_t col)
{
    size_t temp_score = 1;
    int i;
    int j;

    if (is_placeable(row, col) == FALSE 
        || g_boards[row][col] != BLANK) {
        return FALSE;
    }

    g_boards[row][col] = color;

    /* 가로 */
    for (i = col + 1; i < (int)get_column_count(); ++i) {
        if (g_boards[row][i] != (int)color) {
            break;
        } else {
            ++temp_score;
        }
    }

    for (i = col - 1; i > -1; --i) {
        if (g_boards[row][i] != (int)color) {
            break;
        } else {
            ++temp_score;
        }
    }

    if (temp_score >= 5) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - 4;
        } else {
            g_white_score += temp_score - 4;
        }
    }

    temp_score = 1;

    /* 세로 */
    for (i = row + 1; i < (int)get_row_count(); ++i) {
        if (g_boards[i][col] != (int)color) {
            break;
        } else {
            ++temp_score;
        }
    }

    for (i = row - 1; i > -1; --i) {
        if (g_boards[i][col] != (int)color) {
            break;
        } else {
            ++temp_score;
        }
    }

    if (temp_score >= 5) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - 4;
        } else {
            g_white_score += temp_score - 4;
        }
    }

    temp_score = 1;

    /* 대각선 오른쪽 */
    
    i = row - 1;
    j = col - 1;

    while (TRUE) {
        if (i  < 0 || j < 0 || g_boards[i][j] != (int)color) {
            break;
        }
        ++temp_score;
        --i;
        --j;

    }
    
    i = row + 1;
    j = col + 1;

    while (TRUE) {
        if (i > (int)get_row_count() - 1 || j > (int)get_column_count() - 1
            || g_boards[i][j] != (int)color) {
            break;
        }

        ++temp_score;
        ++i;
        ++j;
    }


    if (temp_score >= 5) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - 4;
        } else {
            g_white_score += temp_score - 4;
        }
    }
    temp_score = 1;

    /* 대각선 왼쪽 */

    i = row - 1;
    j = col + 1;

    while (TRUE) {
        if (i < 0 || j > (int)get_column_count() - 1
            || g_boards[i][j] != (int)color) {
            break;
        }

        ++temp_score;
        --i;
        ++j;

    }

    i = row + 1;
    j = col - 1;

    while (TRUE) {
        if (i > (int)get_column_count() - 1 || j < 0
            || g_boards[i][j] != (int)color) {
            break;
        }

        ++temp_score;
        ++i;
        --j;
    }

    if (temp_score >= 5) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - 4;
        } else {
            g_white_score += temp_score - 4;
        }
    }

    return TRUE;
}

int insert_row(const color_t color, const size_t row)
{
    int i;
    int j;

    switch (color) {
        case COLOR_BLACK:
            if (g_black_score < 3 || row > get_row_count() || row > 19) {
                return FALSE;
            } else {
                g_black_score -= 3;
            }
            break;
        case COLOR_WHITE:
            if (g_white_score < 3 || row > get_row_count() || row > 19) {
                return FALSE;
            } else {
                g_white_score -= 3;
            }
            break;
        default:
            return FALSE;
    }

    for (i = get_row_count() - 1; i > (int)row - 1; --i) {
        for (j = 0; j < (int)get_column_count(); ++j) {
            g_boards[i + 1][j] = g_boards[i][j];
        }
    }

    for (i = 0; i < (int)get_column_count(); ++i) {
        g_boards[row][i] = 7;
    }

    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    int i;
    int j;

    switch (color) {
        case COLOR_BLACK:
            if (g_black_score < 3 || col > get_column_count() || col > 19) {
                return FALSE;
            } else {
                g_black_score -= 3;
            }
            break;
        case COLOR_WHITE:
            if (g_black_score < 3 || col > get_column_count() || col > 19) {
                return FALSE;
            } else {
                g_white_score -= 3;
            }
            break;
        default:
            return FALSE;
    }
    printf("==================\n");
    printf("col: %d\n",col);

    for (i = get_column_count() - 1; i > (int)col - 1; --i) {
        for (j = 0; j < (int)get_row_count(); ++j) {
            g_boards[j][i + 1] = g_boards[j][i];
        }
    }

    for (i = 0; i < (int)get_row_count(); ++i) {
        g_boards[i][col] = 7;
    }

    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    int i;
    int j;

    switch (color) {
        case COLOR_BLACK:
            if (g_black_score < 3 || row > get_row_count() - 1 || row > 19) {
                return FALSE;
            } else {
                g_black_score -= 3;
            }
            break;
        case COLOR_WHITE:
            if (g_white_score < 3 || row > get_row_count() || row > 19) {
                return FALSE;
            } else {
                g_white_score -= 3;
            }
            break;
        default:
            return FALSE;
    }

    return TRUE;
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
