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

typedef struct s_dirent_info {
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
} t_dirent_info;

char *mx_add_strings(char *str1, char *str2);
char *mx_get_last_file_or_directory(char *path);



/**
 *          -- Dirent functions --
 * 
 *  dirents are structs that contain information about a file or a dir.
 *  You can also get more detailed information using other tricks. In
 *  this project detailed information is stored in t_dirent_info
 * 
 *  Here are formulas of the following functions:
 * 
 *  mx_dirent_...()       == a function that works with one dirent
 *  mx_dirents_...()      == a function that works with a list/array of dirents
 *  mx_dirent_info_...()  == a function that works with the t_dirent_info struct 
 *  mx_dirent_infos_...() == a function that works with a list/array of the t_dirent_info structs 
*/

void mx_dirent_copy(t_dirent *dest, t_dirent *src); //mx_direntcpy

void mx_dirents_print(int argc, char **argv); //mx_print_dirents
void mx_dirents_sort(t_list *dirent_structures); //mx_sort_dirent_structures
void mx_dirents_print_from_folder(t_dirent *folder); //mx_print_dirent_structures_in_folder
void mx_dirents_free(t_list *dirent_structures_list); //mx_free_dirent_structures
void mx_dirents_print_both(t_list *dirent_structures); //mx_print_files_and_directories
void mx_dirents_print_files(t_list *dirent_structures); //mx_print_files_from_dirent_structures
void mx_dirents_print_folders(t_list *dirent_structures); //mx_print_folders

void mx_dirent_info_free(t_dirent_info *info); //mx_free_detailed_info
void mx_dirent_info_fill(char *filename, t_dirent_info *info); //mx_set_detailed_info

void mx_dirent_infos_sort(t_list *detailed_infos); //mx_sort_detailed_infos
void mx_dirent_infos_free(t_list *detailed_infos); //mx_free_detailed_infos
void mx_dirent_infos_print(t_list *detailed_infos); //mx_print_detailed_infos
void mx_dirent_infos_print_from_folder(t_dirent *folder, t_list *detailed_infos); //mx_print_detailed_infos_in_folder

t_list *mx_dirents_get(const char *name); //mx_get_dirent_structures
t_list *mx_dirents_get_from_main_input(char **argv, int argc); //mx_get_dirent_structures_from_array

t_dirent *mx_dirent_get(char *name); //mx_get_dirent_structure

t_list *mx_dirent_infos_get(t_dirent *folder); //mx_get_detailed_infos
t_list *mx_dirents_parse_to_dirent_infos(t_list *dirent_structurs); //mx_parse_dirents_to_detailed_infos


void mx_check_l_flag(int argc, char **argv);
void mx_try_opendir(DIR **dir, const char *name);
void mx_handle_l_flag(t_list *dirent_structures);

void mx_print_total(t_list *detailed_infos);

/**
 *          -- Uls functions --
 * 
 *  These functions are the ones you're probably intersted in.
 *  They represent the actual calls of the uls command. 
 * 
 *  Here is a formula of the following functions: mx_call_uls_...()      
 * 
 *  mx_call_uls_l()              == ~$./uls -l
 *  mx_call_uls_cat_e()          == ~$./uls | cat -e
 *  mx_call_uls_with_params()    == ~$./uls [-l] argv[1], argv[2], ..., argv[N] (-l is optional)
 *  mx_call_uls_without_params() == ~$./uls  
*/

void mx_call_uls_l();
void mx_call_uls_cat_e();
void mx_call_uls_without_params(char *path);
void mx_call_uls_with_params(int argc, char *argv[]);
