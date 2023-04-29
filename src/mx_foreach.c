#include "../inc/uls_foreach.h"

void mx_foreach_t_dirent(t_list *dirent_structures, void (*f)(t_dirent *)) {
    if (!dirent_structures) return;

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        f(temp);
    }
}

void mx_foreach_t_dirent_in_list(t_list *dirent_structures, void (*f)(t_dirent *, t_list *dirent_structures)) {
    if (!dirent_structures) return;

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        f(temp, dirent_structures);
    }
}

void mx_foreach_t_dirent_and_iterator(t_list *dirent_structures, void (*f)(t_dirent *, t_list *i)) {
    if (!dirent_structures) return;

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        f(temp, i);
    }
}

void mx_t_dirent_free(t_dirent *temp) {
    free(temp);
}

void mx_t_dirent_print_name(t_dirent *temp) {
    if (temp->d_type == DT_REG && !mx_is_hidden_file(temp->d_name)) {
        mx_printstrc(temp->d_name, ' ');
    }
}

void mx_foreach_print_dirent(t_dirent *temp, t_list *i) {
    if (!mx_is_hidden_file(temp->d_name)) {
        mx_printstr(temp->d_name);
        
        if (i->next != NULL) {
            mx_printchar(SPACE);    
            mx_printchar(SPACE);
        }
    }
}

void mx_t_dirent_print_name_newline(t_dirent *temp) {
    if (!mx_is_hidden_file(temp->d_name)) {
        mx_printstrc(temp->d_name, '\n');
    }
}

void mx_t_dirent_print_folder(t_dirent *temp) {
    if (temp->d_type == DT_DIR && !mx_is_hidden_file(temp->d_name)) {
        mx_printchar('\n');
        mx_dirents_print_from_folder(temp);
    }
}
