#pragma once
#include "../inc/libmx/inc/libmx.h"

t_winsize mx_get_winsize(); 

char *mx_add_strings(char *str1, char *str2);
char *mx_remove_last_directory_move(char *path);
char *mx_get_last_file_or_directory(char *path);
