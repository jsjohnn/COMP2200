/* */

#include <stdio.h>
#include "pomoku.h"


typedef enum color {
    COLOR_BLACK = 1,
	COLOR_WHITE

} color_t;

void init_game(void) {

	int boards[20][20] = {0,};
	
	int black_score = 0;
	int white_score = 0;
		
}

size_t get_row_count(void) {
	return sizeof(boards) / sizeof(boards[0]);

}

size_t get_column_count(void) {
	return sizeof(boards[0]) / sizeof(int);

}

int get_color(const size_t row, const size_t col) {
	int blank = -1;
	if (boards[row][col] == 0) {
		return blank;
	}

	if (boards[row][col] == 1) {
		return 0;
}

int is_placeable(const size_t row, const size_t col) {
	if (boards[row,col] != 0) {
		return FALSE;

	}
	
	if (row >= get_row_count() || col >= get_column_count()) {
		return FALSE;
	}

	return TRUE;

}
int place_stone(const color_t color, const size_t row, const size_t col) {
	if (is_placeable == FALSE) {
		return FALSE;
	}
	
	if (color < 0 || color > 1) {
		return FALSE;

	}

	boards[row, col] = color_t;
	return TRUE;

}

