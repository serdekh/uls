#define _DEFAULT_SOURCE
#include <dirent.h>

#include <errno.h>
#include <stdbool.h>

#include "../inc/libmx/inc/libmx.h"

#define CURRENT_DIRECTORY "."
#define FLAG__HIDDEN_FILES_PRINTED "-a"
#define FLAG__MORE_INFORMATATION_PRINTED "-l"

typedef struct dirent t_dirent;

/**
 * @brief sorts a list of dirent structures
 * @param dirent_structures a list of dirent structures
 * @return Nothing but sorts the input list
*/
void mx_sort_dirent_structures(t_list *dirent_structures);

/**
 * @brief frees all the memory in the list allocated by mx_get_dirent_structures() function
 * @param dirent_structures_list list of dirent structures
 * @return If pointer is NULL, function returns.
*/
void mx_free_dirent_structures(t_list *dirent_structures_list);

/**
 * @brief uses opendir and readdir funcs to get all files in a directory converted into dirent structures
 * @param name directory path
 * @return list of dirent structures with a dynamic memory. Requires freeing by mx_free_dirent_structures
*/
t_list *mx_get_dirent_structures(const char *name);

/**
 * @brief reads a `dirent_structures` list and prints d_name field of them in stdout
 * @param dirent_structures dynamic list of dirent structs to be printed
 * @param hidden_are_printed if true, then hidden files will be printed
 * @return nothing. If file pointer is NULL, function returns
*/
void mx_print_files_and_directories(t_list *dirent_structures, bool hidden_are_printed);

/**
 * @brief calls opendir() function from dirent.h but also checks if opening dir was successful.
 * If opening failed, then program stops working and returns 1. Otherwise, sets current directory
 * to the dir pointer
 * 
 * @param dir pointer which will be set with a {name} directory
 * @param name directory path which will be set to a {dir} struct
 * @return nothing but if opening file fails, program stops working and returns 1 by exit() function
*/
void mx_try_opendir(DIR **dir, const char *name);

/**
 * @brief copies data from SRC to DEST
 * @param dest dirent structure (should be dynamically allocated)
 * @param src dirent structure with data that will be copied to dest
 * @return nothing. If one of pointers are NULL, the function returns
*/
void mx_direntcpy(t_dirent *dest, t_dirent *src);


/* The actual uls functions thatt represent the cmd calls*/

/**
 * @brief calls 'uls' command without any parameters and prints files/dirs
 * in the alphabet order from the current directory
 * @return 0 if success or 1 if failed
*/
void mx_uls_no_params();

