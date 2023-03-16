#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
	t_list *node = mx_create_node(data);

    if (*list == NULL) {
        *list = node;
        return;
    }

    t_list *temporary = *list;

    while (temporary->next != NULL) {
        temporary = temporary->next;
    }

    temporary->next = node;
}

