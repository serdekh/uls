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
#define NO_PERMISSIONS_STRING "d---------"

typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct dirent t_dirent;
typedef struct winsize t_winsize;
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

bool mx_dirents_print_files(t_list *dirent_structures); 

void mx_dirent_copy(t_dirent *dest, t_dirent *src);

void mx_dirents_print(int argc, char **argv); 
void mx_dirents_sort(t_list *dirent_structures); 
void mx_dirents_print_from_folder(t_dirent *folder); 
void mx_dirents_free(t_list *dirent_structures_list); 
void mx_dirents_print_both(t_list *dirent_structures); 
void mx_dirents_print_folders(t_list *dirent_structures, t_list *all);

void mx_dirent_info_free(t_dirent_info *info); 
void mx_dirent_info_fill(char *filename, t_dirent_info *info); 

void mx_dirent_infos_sort(t_list *detailed_infos); 
void mx_dirent_infos_free(t_list *detailed_infos); 
bool mx_dirent_infos_print(t_list *detailed_infos); 
void mx_dirent_infos_print_from_folder(t_list *detailed_infos);

t_list *mx_dirents_get(const char *name); 
t_list *mx_dirents_get_from_main_input(char **argv, int argc); 

t_list *mx_dirent_infos_get(t_dirent *folder);
t_list *mx_dirents_parse_to_dirent_infos(t_list *dirent_structurs);
t_list *mx_dirents_get_of_type(t_list *dirents, unsigned char type);

t_dirent *mx_dirent_new();
t_dirent *mx_dirent_get(char *name); 
t_dirent **mx_dirents_parse_to_array(t_list *dirents, size_t *size);

t_dirent_info *mx_dirent_info_new();



void mx_check_l_flag(int argc, char **argv);
void mx_try_opendir(DIR **dir, const char *name, bool exit_program);
void mx_handle_l_flag(t_list *dirent_structures);

void mx_print_total(t_list *detailed_infos);



void mx_print_table(t_dirent **dirents, size_t size, t_list *current_folder);



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
void mx_call_uls_without_params(char *path, bool exit_program);
void mx_call_uls_with_params(int argc, char *argv[]);
