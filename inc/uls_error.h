#pragma once

#define SUCCESS 0
#define FAILURE 1
#define ULS_USAGE "usage: uls [-l] [file ...]\n"

void mx_check_flag_l_position(int argc, char **argv);
void mx_print_invalid_option(char **argv);
