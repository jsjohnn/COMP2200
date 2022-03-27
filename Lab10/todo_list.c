#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t my_todo_list;

    my_todo_list.max_count = max_size;
    my_todo_list.cur_count = 0;
    my_todo_list.next = NULL;
    
    return my_todo_list;
    
}

// TODO: add 함수 구현 후에 구현
void finalize_todo_list(todo_list_t* todo_list)
{
    size_t i = 0;   
    todo_list_t* tmp_list;

    while (todo_list->next != NULL) {
        ++i;
        if (i == 1) {
            todo_list = todo_list->next;
            continue;
        }
        tmp_list = todo_list;
        todo_list = todo_list->next;
        free(tmp_list);
        
    }
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->max_count == 0 || (todo_list->cur_count == todo_list->max_count)) {
        return false;
    }

    if (todo_list->cur_count == 0) {

        todo_list->priority = priority;
        todo_list->cur_count = 1;

        strncpy(todo_list->str, task, LENGTH);
        todo_list->str[LENGTH - 1] = '\0';
        todo_list->str[strlen(task)] = '\0';

        return true;

    }

    todo_list_t* tmp_todo_list = todo_list;


    while (todo_list->next != NULL) {
        todo_list->cur_count = (todo_list->cur_count) + 1;
        todo_list = todo_list->next;
    }

    if (todo_list->cur_count == 1 && todo_list->next == NULL) {
        todo_list->cur_count = (todo_list->cur_count) + 1;
    }

    todo_list_t* tmp_list = malloc(sizeof(todo_list_t));
    todo_list->next = tmp_list;

    tmp_list->max_count = todo_list->max_count;
    tmp_list->cur_count = (todo_list->cur_count) + 1;

    tmp_list->priority = priority;
    strncpy(tmp_list->str, task, sizeof(tmp_list->str));
    tmp_list->str[sizeof(tmp_list->str) - 1] = '\0';
    tmp_list->str[strlen(task)] = '\0';

    tmp_list->next = NULL;

    todo_list = tmp_todo_list;

    return true;
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->cur_count;
}

bool is_empty(const todo_list_t* todo_list)
{
    if ((todo_list->cur_count) == 0) {
        return true;
    } 

    return false;
}

bool complete_todo(todo_list_t* todo_list)
{
    return false;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    return NULL;
}

