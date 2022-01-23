#include <stdio.h>
#include <limits.h>
#include "pomoku.h"

#define BLANK (7)
#define OUT_OF_RANGE_COL_OR_ROW (-1)

#define MIN_LENGTH (10)
#define MAX_LENGTH (20)

#define GET_SCORE_POINT (5)
#define DUMP_SCORE (4)
#define ONE_SCORE (1)

#define INSERT_OR_REMOVE_REQUIRED_POINT (3)
#define SWAP_REQUIRED_POINT (2)
#define COPY_REQUIRED_POINT (4)

int g_black_score = 0;
int g_white_score = 0;
int g_boards[20][20];

void init_game(void)
{
    size_t i;
    size_t j;

    g_black_score = 0;
    g_white_score = 0;

    for (i = 0; i < MAX_LENGTH; ++i) {
        for (j = 0; j < MAX_LENGTH; ++j) {
            g_boards[i][j] = OUT_OF_RANGE_COL_OR_ROW;
        }
    }

    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 15; ++j) {
            g_boards[i][j] = BLANK;
        }
    }
}

size_t get_row_count(void)
{
    size_t i;

    for (i = 0; i < MAX_LENGTH; ++i) {
        if (g_boards[i][0] == OUT_OF_RANGE_COL_OR_ROW) {
            return i;
        }
    }

    return (size_t)-1;
}

size_t get_column_count(void)
{
    size_t i;

    for (i = 0; i < MAX_LENGTH; ++i) {
        if (g_boards[0][i] == OUT_OF_RANGE_COL_OR_ROW) {
            return i;
        }
    }
    return (size_t)-1;
}

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

int get_color(const size_t row, const size_t col)
{
    if (row < 0 || col < 0 || row > get_row_count() - 1  
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

int is_placeable(const size_t row, const size_t col)
{
    if (row < 0 ||  col < 0 || row > get_row_count() - 1
        || col > get_column_count() - 1 || g_boards[row][col] != BLANK) {
        return FALSE;
    }  
    
    return TRUE;
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    size_t temp_score = ONE_SCORE;
    int i;
    int j;

    if (is_placeable(row, col) == FALSE || g_boards[row][col] != BLANK) {
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

    if (temp_score >= GET_SCORE_POINT) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - DUMP_SCORE;
        } else {
            g_white_score += temp_score - DUMP_SCORE;
        }
    }

    temp_score = ONE_SCORE;

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

    if (temp_score >= GET_SCORE_POINT) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - DUMP_SCORE;
        } else {
            g_white_score += temp_score - DUMP_SCORE;
        }
    }

    temp_score = ONE_SCORE;

    /* 대각선 (＼) */
    i = row - 1;
    j = col - 1;

    while (TRUE) {
        if (i < 0 || j < 0 || g_boards[i][j] != (int)color) {
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

    if (temp_score >= GET_SCORE_POINT) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - DUMP_SCORE;
        } else {
            g_white_score += temp_score - DUMP_SCORE;
        }
    }

    temp_score = ONE_SCORE;

    /* 대각선 (/)*/
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
        if (j < 0 || i > (int)get_column_count() - 1
            || g_boards[i][j] != (int)color) {
            break;
        }

        ++temp_score;
        ++i;
        --j;
    }

    if (temp_score >= GET_SCORE_POINT) {
        if (color == COLOR_BLACK) {
            g_black_score += temp_score - DUMP_SCORE;
        } else {
            g_white_score += temp_score - DUMP_SCORE;
        }
    }

    return TRUE;
}

int insert_row(const color_t color, const size_t row)
{
    int i;
    int j;

    if (get_row_count() >= MAX_LENGTH) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < INSERT_OR_REMOVE_REQUIRED_POINT || row > get_row_count()) {
            return FALSE;
        } else {
            g_black_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < INSERT_OR_REMOVE_REQUIRED_POINT || row > get_row_count()) {
            return FALSE;
        } else {
            g_white_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
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
        g_boards[row][i] = BLANK;
    }

    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    int i;
    int j;

    if (get_column_count() >= MAX_LENGTH) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < INSERT_OR_REMOVE_REQUIRED_POINT || col > get_column_count()) {
            return FALSE;
        } else {
            g_black_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < INSERT_OR_REMOVE_REQUIRED_POINT || col > get_column_count()) {
            return FALSE;
        } else {
            g_white_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = get_column_count() - 1; i > (int)col - 1; --i) {
        for (j = 0; j < (int)get_row_count(); ++j) {
            g_boards[j][i + 1] = g_boards[j][i];
        }
    }

    for (i = 0; i < (int)get_row_count(); ++i) {
        g_boards[i][col] = BLANK;
    }

    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    int i;
    int j;
    int last_row = get_row_count() - 1;

    if (get_row_count() <= MIN_LENGTH) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < INSERT_OR_REMOVE_REQUIRED_POINT || row > get_row_count() - 1) {
            return FALSE;
        } else {
            g_black_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < INSERT_OR_REMOVE_REQUIRED_POINT || row > get_row_count() - 1) {
            return FALSE;
        } else {
            g_white_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = row + 1; i < (int)get_row_count(); ++i) {
        for (j = 0; j < (int)get_column_count(); ++j) {
            g_boards[i - 1][j] = g_boards[i][j];
        }
    }

    for (i = 0; i < (int)get_column_count(); ++i) {
        g_boards[last_row][i] = -1;
    }

    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    int i;
    int j;
    int last_col = get_column_count() - 1;

    if (get_column_count() <= MIN_LENGTH) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < INSERT_OR_REMOVE_REQUIRED_POINT || col > get_column_count() - 1) {
            return FALSE;
        } else {
            g_black_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < INSERT_OR_REMOVE_REQUIRED_POINT || col > get_column_count() - 1) {
            return FALSE;
        } else {
            g_white_score -= INSERT_OR_REMOVE_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = col + 1; i < (int)get_column_count(); ++i) {
        for (j = 0; j < (int)get_row_count(); ++j) {
            g_boards[j][i - 1] = g_boards[j][i];
        }
    }

    for (i = 0; i < (int)get_row_count(); ++i) {
        g_boards[i][last_col] = -1;
    }

    return TRUE;
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    size_t last_row = get_row_count() - 1;

    if (row0 > last_row || row1 > last_row || row0 < 0 || row1 < 0) {
        return FALSE;
    }
    
    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < SWAP_REQUIRED_POINT) {
            return FALSE;
        } else {
            g_black_score -= SWAP_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < SWAP_REQUIRED_POINT) {
            return FALSE;
        } else {
            g_white_score -= SWAP_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = 0; i < get_column_count(); ++i) {
        g_boards[row0][i] ^= g_boards[row1][i];
        g_boards[row1][i] ^= g_boards[row1][i];
        g_boards[row0][i] ^= g_boards[row1][i];
    }

    return TRUE;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    size_t last_col = get_column_count() - 1;

    if (col0 > last_col || col1 > last_col || col0 < 0 || col1 < 0) {
        return FALSE;
    }
    
    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < SWAP_REQUIRED_POINT) {
            return FALSE;
        } else {
            g_black_score -= SWAP_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < SWAP_REQUIRED_POINT) {     
            return FALSE;
        } else {
            g_white_score -= SWAP_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }
    
    for (i = 0; i < get_row_count(); ++i) {
        g_boards[i][col0] ^= g_boards[i][col1];
        g_boards[i][col1] ^= g_boards[i][col1];
        g_boards[i][col0] ^= g_boards[i][col1];
    }

    return TRUE;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t last_row = get_row_count() - 1;

    if (src > last_row || dst > last_row || src < 0 || dst < 0) {
        return FALSE;
    }
    
    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < COPY_REQUIRED_POINT) {
            return FALSE;
        } else {
            g_black_score -= COPY_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < COPY_REQUIRED_POINT) {     
            return FALSE;
        } else {
            g_white_score -= COPY_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = 0; i < get_column_count(); ++i) {
        g_boards[dst][i] = g_boards[src][i];
    }

    return TRUE;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    size_t last_col = get_column_count() - 1;


    if (src > last_col || src < 0 || dst > last_col || dst < 0) {
        return FALSE;
    }
    
    switch (color) {
    case COLOR_BLACK:
        if (g_black_score < COPY_REQUIRED_POINT) {
            return FALSE;
        } else {
            g_black_score -= COPY_REQUIRED_POINT;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score < COPY_REQUIRED_POINT) {     
            return FALSE;
        } else {
            g_white_score -= COPY_REQUIRED_POINT;
        }
        break;
    default:
        return FALSE;
    }

    for (i = 0; i < get_row_count(); ++i) {
        g_boards[i][dst] = g_boards[i][src];
    }

    return TRUE;
}

void view_ary(void)
{
    size_t i;
    size_t j;

    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 20; ++j) {
            printf("%2d", g_boards[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
}

