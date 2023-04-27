#pragma once

#define ULS_USAGE "usage: uls [-l] [file ...]\n"

void mx_check_flag_l_position(int argc, char **argv);
void mx_print_invalid_option(char **argv);
void mx_print_no_such_file_or_directory(char *file);
