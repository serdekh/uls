#pragma once
#define _DEFAULT_SOURCE
#include <dirent.h>

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "../inc/libmx/inc/libmx.h"

#define SPACE ' '
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

char *mx_add_strings(char *str1, char *str2);
char *mx_get_last_file_or_directory(char *path);

t_list *mx_get_dirent_structures(const char *name);
t_list *mx_get_dirent_structures_from_array(char **argv, int argc);

t_dirent *mx_get_dirent_structure(char *name);

void mx_check_l_flag(int argc, char **argv);
void mx_try_opendir(DIR **dir, const char *name);
void mx_direntcpy(t_dirent *dest, t_dirent *src);
void mx_handle_l_flag(t_list *dirent_structures);
void mx_sort_detailed_infos(t_list *detailed_infos);
void mx_free_detailed_infos(t_list *detailed_infos);
void mx_free_detailed_info(t_detailed_information *info);
void mx_sort_dirent_structures(t_list *dirent_structures);
void mx_free_dirent_structures(t_list *dirent_structures_list);
void mx_set_detailed_info(char *filename, t_detailed_information *info);

void mx_print_total(t_list *detailed_infos);
void mx_print_dirents(int argc, char **argv);
void mx_print_folders(t_list *dirent_structures);
void mx_print_detailed_infos(t_list *detailed_infos);
void mx_print_dirent_structures_in_folder(t_dirent *folder);
void mx_print_files_from_dirent_structures(t_list *dirent_structures);
void mx_print_files_and_directories(t_list *dirent_structures);
t_list *mx_get_detailed_infos(t_dirent *folder); 
void mx_print_detailed_infos_in_folder(t_dirent *folder, t_list *detailed_infos);
t_list *mx_parse_dirents_to_detailed_infos(t_list *dirent_structurs);

// ---------------- The actual uls functions that represent the cmd calls ----------------

void mx_call_uls_without_params(char *path);
void mx_call_uls_with_params(int argc, char *argv[]);
void mx_call_uls_l();
