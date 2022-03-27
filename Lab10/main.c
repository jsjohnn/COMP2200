#include <stdio.h>
#include <assert.h>
#include "todo_list.h"

int main(void)
{

    todo_list_t todo_list = init_todo_list(9);

    assert(is_empty(&todo_list));

    assert(add_todo(&todo_list, 10, "A"));
    assert(add_todo(&todo_list, 22, "B"));
    assert(add_todo(&todo_list, 3, "C"));
    assert(add_todo(&todo_list, 34, "D"));
    assert(add_todo(&todo_list, 20, "E"));
    assert(add_todo(&todo_list, 59, "F"));
    assert(add_todo(&todo_list, 60, "G"));
    assert(add_todo(&todo_list, 55, "H"));
    assert(add_todo(&todo_list, 22, "I"));

    assert(todo_list.max_priority_num == 60);

    //complete_todo(&todo_list);


    assert(get_count(&todo_list) == 9);
    return 0;
}
