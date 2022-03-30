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
    my_todo_list.max_priority_num = 0;
    
    return my_todo_list;
    
}

void finalize_todo_list(todo_list_t* todo_list)
{
    size_t i = 0;   
    todo_list_t* tmp_list;
    

    while (todo_list->next != NULL) {
        tmp_list = todo_list;
        todo_list = todo_list->next;
        free(tmp_list);
        
    }
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->max_count == 0 || (todo_list->cur_count >= todo_list->max_count)) {
        return false;
    }

    if (todo_list->cur_count == 0) {

        task_t* tmp_task = malloc(sizeof(task_t));
        todo_list->next = tmp_task;
        todo_list->cur_count = 1;
        todo_list->max_priority_num = priority;
        
        tmp_task->priority = priority;
        tmp_task->priority = NULL;
        strncpy(tmp_task->str, task, LENGTH);
        tmp_task->str[LENGTH - 1] = '\0';
        tmp_task->str[strlen(task)] = '\0';
        
        return true;

    }

    if (todo_list->max_priority_num < priority) {
        todo_list->max_priority_num = priority;
    }


    while (todo_list->next != NULL) {
        todo_list = todo_list->next;
    }


    

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
    
    if (todo_list->cur_count == 0) {
        return false;
    }

    if (todo_list->cur_count == 1) {
        (todo_list->str)[0] = '\0';
        todo_list->priority = 0;
        todo_list->cur_count = 0;
        todo_list->max_priority_num = 0;

        return true;

    }

    todo_list_t* tmp_todo_list = todo_list;
    
    todo_list_t* tmp_p;
    
    int max_priority = todo_list->max_priority_num;

    while (todo_list->next != NULL) {
        if (max_priority == todo_list->next->priority) {
            todo_list->next = todo_list->next->next;
            free(todo_list->next);
            return true;
        }

        if (todo_list->next->next == NULL) {
            tmp_p = todo_list->next->next;
            todo_list->next = todo_list->next->next;
            free(tmp_p);
            return true;
            
        }

        todo_list = todo_list->next;


    }

    todo_list = tmp_todo_list;

    int tmp_max = 0;

    while (todo_list->next != NULL) {
        if (tmp_max < todo_list->max_priority_num) {
            tmp_max = todo_list->max_priority_num;
        }
    }

    if (tmp_max < todo_list->max_priority_num) {
        tmp_max = todo_list->max_priority_num;
    }

    todo_list = tmp_todo_list;
    

    todo_list = NULL;

    assert(todo_list == NULL);


    return false;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    todo_list = NULL;

    assert(todo_list == NULL);
    
    return NULL;
}



