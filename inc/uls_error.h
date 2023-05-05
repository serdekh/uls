#pragma once

#define ULS_USAGE "usage: uls [-l] [file ...]\n"

bool mx_check_flag_l_position(int argc, char **argv);
void mx_print_invalid_option(char *flag);
void mx_print_no_such_file_or_directory(char *file, bool exit_program);
void mx_set_error_and_print(int errno_value, char *file, bool exit_program, bool newline);

