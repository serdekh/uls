#pragma once
#include "../inc/libmx/inc/libmx.h"

t_winsize mx_get_winsize(); 

char *mx_add_strings(char *str1, char *str2);
char *mx_remove_last_directory_move(char *path);
char *mx_get_last_file_or_directory(char *path);

bool mx_doesnt_have_permissions(t_dirent_info *dirent_info);
void mx_newline();
int mx_get_size_without_non_permission_folders(t_list *folders);
