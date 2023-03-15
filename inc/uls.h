#define _DEFAULT_SOURCE
#include <dirent.h>

#include <errno.h>
#include <stdbool.h>

#include "../inc/libmx/inc/libmx.h"

#define CURRENT_DIRECTORY "."
#define FLAG__HIDDEN_FILES_PRINTED "-a"

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

/* Functions note */

// write        (KNOW!)               - function that prints data into a descriptor
// malloc       (KNOW!)               - function to allocate dynamic memory
// free         (KNOW!)               - function to free dynamic memory;
// exit         (KNOW!)               - kills the process of a program and returns 1 or 0
// malloc_size  (KNOW!)               - returns size of an allocated memory
// strerror     (KNOW!)               - prints error from 'errno' variable
// opendir      (KNOW!)               - opens a stream with a directory and returns a pointer to it
// readdir      (KNOW!)               - returns a dirent struct that represents a file/dir in a current one
// closedir     (KNOW!)               - closes the stream of an opendir function

// stat         (DON'T KNOW!)         - ?
// lstat        (DON'T KNOW!)         - ?
// getpwuid     (DON'T KNOW!)         - ?
// getgrgid     (DON'T KNOW!)         - ?
// listxattr    (DON'T KNOW!)         - ?
// getxattr     (DON'T KNOW!)         - ?
// readlink     (DON'T KNOW!)         - ?
// ioctl        (DON'T KNOW!)         - ?
// issaty       (DON'T KNOW!)         - ?
// acl_get_file (DON'T KNOW!)         - ?
// acl_to_text  (DON'T KNOW!)         - ?
// acl_free     (DON'T KNOW!)         - ?

// perror       (NOT COMPLETELY KNOW) - function to print error in stderr. Maybe works with errno?
// time         (NOT COMPLETELY KNOW) - function to calculate how long program works?
// ctime        (NOT COMPLETELY KNOW) - function to calculate how long program works? 
// errno        (NOT COMPLETELY KNOW) - saves error to a global variable?
