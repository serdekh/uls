#pragma once
#include "./uls.h"

void mx_foreach_t_dirent(t_list *dirent_structures, void (*f)(t_dirent *));
void mx_foreach_t_dirent_and_iterator(t_list *dirent_structures, void (*f)(t_dirent *, t_list *i));
void mx_foreach_t_dirent_in_list(t_list *dirent_structures, void (*f)(t_dirent *, t_list *dirent_structures));
void mx_foreach_print_dirent(t_dirent *temp, t_list *i);

void mx_t_dirent_free(t_dirent *temp);
void mx_t_dirent_print_name(t_dirent *temp, t_list *i);
void mx_t_dirent_print_folder(t_dirent *temp);
void mx_t_dirent_print_name_newline(t_dirent *temp); 


