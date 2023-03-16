#include "../inc/uls.h"

void mx_print_files_and_directories(t_list *dirent_structures, bool hidden_are_printed) {
    if (!dirent_structures) return;

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        bool only_not_hidden_printed = !mx_is_hidden_file(temp->d_name) && !hidden_are_printed;

        if (hidden_are_printed || only_not_hidden_printed) {
            mx_printstrc(temp->d_name, ' ');
            mx_printchar(' ');
        }
    }
}