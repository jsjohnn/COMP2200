#include <stdio.h>
#include <limits.h>
#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{

	int i;
	for(i = 0; i < (int)element_count; ++i)
	{
		if (num == numbers[i])
		{
			return i;
		}
	}

	return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
	int i;

	for (i = element_count; i >= 0; --i)
	{
		if (num == numbers[i])
		{			
			return i;
		}
	}

	return -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
	int i;
	int max_value;
	int max_index = 0;

	if (element_count == 0)
	{
		return -1;
	}
	
	max_value = numbers[0];
	
	for (i = 1; i < (int)element_count; ++i)
	{
		if (numbers[i] > max_value)
		{
			max_value = numbers[i];
			max_index = i;
		}
	}

	return max_index;
	
}

int get_min_index(const int numbers[], const size_t element_count)
{
	int i;
	int min_value;
	int min_index = 0;

	if (element_count == 0)
	{
		return -1;
	}

	min_value = numbers[0];
	for (i = 1; i < (int)element_count; ++i)
	{
		if (numbers[i] < min_value)
		{
			min_value = numbers[i];
			min_index = i;
		}
	}

	return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
	int i;

	if (element_count == 0)
	{
		return FALSE;
	}

	for (i = 0; i < (int)element_count; ++i)
	{
		if (numbers[i] < 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
	int i;

	if (element_count == 0)
	{
		return FALSE;
	}

	for (i = 0; i < (int)element_count; ++i)
	{
		if (numbers[i] % 2 == 0)
		{
			return TRUE;
		}
	}
	
	return FALSE;

}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
	
	int i = element_count;
	int temp;
	
	if (element_count < pos )
	{
		return FALSE;
	}
	
	while(TRUE)
	{
		if (i == (int)pos)
		{
			numbers[i] = num;
			return TRUE;
		}
		temp = numbers[i - 1];
		numbers[i] = temp;
		--i;
	}
	
	return FALSE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
	int i;
	int temp;
	
	if (element_count < index)
	{
		return FALSE;
	}

	for (i = index; i < (int)(element_count - 1); ++i)
	{
		temp = numbers[i + 1];
		numbers[i] = temp;
	}
	
	numbers[element_count - 1] = INT_MIN;

	return TRUE;

}

