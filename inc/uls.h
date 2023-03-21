#pragma once
#define _DEFAULT_SOURCE
#include <dirent.h>

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "../inc/libmx/inc/libmx.h"

#define SPACE ' '
#define SUCCESS 0
#define FAILURE 1
#define ULS_USAGE "usage: uls [-l] [file ...]\n"
#define FLAG_CHAR '-'
#define CURRENT_DIRECTORY "."

typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct dirent t_dirent;
typedef struct timespec t_timespec;

typedef struct s_detailed_information {
    char permissions_string[11];
    char *owner_name;
    char *group_name;
    char *month;
    char *day;
    char *time;
    char *file_name;
    int size;
    int hard_links;
    int block_size;
} t_detailed_information;


t_list *mx_get_dirent_structures(const char *name);

void mx_print_total(t_list *detailed_infos);
void mx_try_opendir(DIR **dir, const char *name);
void mx_direntcpy(t_dirent *dest, t_dirent *src);
void mx_handle_l_flag(t_list *dirent_structures);
void mx_sort_detailed_infos(t_list *detailed_infos);
void mx_free_detailed_infos(t_list *detailed_infos);
void mx_print_detailed_infos(t_list *detailed_infos);
void mx_sort_dirent_structures(t_list *dirent_structures);
void mx_free_dirent_structures(t_list *dirent_structures_list);
void mx_set_detailed_info(char *filename, t_detailed_information *info);
void mx_print_files_and_directories(t_list *dirent_structures, bool hidden_are_printed);

// ---------------- The actual uls functions that represent the cmd calls ----------------

void mx_uls_no_params(char *path);
void mx_uls_with_params(int argc, char *argv[]);
